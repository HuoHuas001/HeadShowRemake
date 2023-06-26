/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/LoggerAPI.h>
#include <llapi/ScheduleAPI.h>
#include <llapi/RemoteCallAPI.h>
#include <llapi/utils/PlayerMap.h>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/Scoreboard.hpp>
#include <llapi/EventAPI.h>
#include <Nlohmann/json.hpp>
#include "version.h"
#include "BaseLib.h"

using nlohmann::json;

extern Logger logger;

// PlayerMap
playerMap<string> ORIG_NAME;
std::function<std::string(std::string const& a1, std::string const& a2)> PAPIgetValueByPlayerAPI;
std::function<long long(std::string const& xuid)> LLMoneyGet;

// Config
string defaultString = "%player_realname%\n§c❤§b%player_max_health%§e/§a%player_health% §b%player_max_hunger%§e/§a%player_hunger%\n§f%player_device% §c%player_ping%ms";
json defaultScoreBoard;
int defaultTick = 20;

bool readJson()
{
    json j; // 创建 json 对象
    std::ifstream jfile("plugins/HeadShow/config.json");
    if (jfile)
    {
        jfile >> j; // 以文件流形式读取 json 文件
        defaultTick = j.at("updateTick");
        defaultString = j.at("showTitle");
        defaultScoreBoard = j["scoreBoard"];
        return true;
    }
    else
    {
        logger.warn("No config.json file was detected. Please confirm whether the installation package is complete");
        return false;
    }
}

// Update Head Info
void updateHead()
{
    for (auto pl : Level::getAllPlayers())
    {
        try{
            // Init Var
            std::unordered_map<string, string> ud = {};
            string _defaultString = defaultString;

            // Save Player's realName
            string playerRealName = pl->getRealName();
            ORIG_NAME[(ServerPlayer *)pl] = playerRealName;

            // get Player's Scoreboard Score
            if (defaultScoreBoard.size() != 0)
            {
                for (auto it = defaultScoreBoard.begin(); it != defaultScoreBoard.end(); ++it)
                {
                    string score = std::to_string(pl->getScore((string)it.value()));
                    ud["%" + it.key() + "%"] = score;
                }
            }

            // get Player's LLMoney
            if (LLMoneyGet)
            {
                string money = std::to_string(LLMoneyGet(pl->getXuid()));
                ud["%money%"] = money;
            }

            // 格式化接入PAPI
            string sinfo = PAPIgetValueByPlayerAPI(_defaultString, pl->getXuid());
            sinfo = forEachReplace(ud, sinfo);

            // 设置NameTag
            pl->rename(sinfo);
        }
        catch(...){}
        
    }
    return;
}

// Edit Return Name
/*?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ*/
THook(string &, "?getNameTag@Actor@@UEBAAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ", void *x)
{
    if (auto it = ORIG_NAME._map.find((ServerPlayer *)x); it != ORIG_NAME._map.end())
    {
        return it->second;
    }
    return original(x);
}

// Player Hurt Edited.
/*?change@HealthAttributeDelegate@@UEAAMMMAEBVAttributeBuff@@@Z*/
THook(long long, "?change@HealthAttributeDelegate@@UEAAMMMAEBVAttributeBuff@@@Z", __int64 a1, float a2, float a3, __int64 a4)
{
    Actor *ac = *(Actor **)(a1 + 32);
    if (ac->getTypeName() == "minecraft:player")
    {
        updateHead();
    }
    return original(a1, a2, a3, a4);
}

// Init Plugins
void PluginInit()
{
    // read Config json.
    if (bool re = readJson())
        logger.info("HeadShow read Config success.");
    logger.info("HeadShow Remake Version Loaded.");

    Event::ServerStartedEvent::subscribe([](Event::ServerStartedEvent ev)
                                         {
		//开始替换
		Schedule::repeat(updateHead, defaultTick);
		//检查计分板
		if (defaultScoreBoard.size() != 0) {
			for (auto it = defaultScoreBoard.begin(); it != defaultScoreBoard.end(); ++it) {
				string board = (string)it.value();
				if (!::Global<Scoreboard>->getObjective(board)) {
					auto obj = Scoreboard::newObjective(board, board);
					logger.warn("Failed to find " + board + ", created automatically");
				}
			}
		}
        // BePlaceHolder Call Function
        PAPIgetValueByPlayerAPI = RemoteCall::importAs<std::string(std::string const& str, std::string const& xuid)>("BEPlaceholderAPI", "translateString");

        if(ll::getPlugin("LLMoney"))
            LLMoneyGet = RemoteCall::importAs<long long(std::string const& xuid)>("LLMoney", "LLMoneyGet");

        return true; });
}
