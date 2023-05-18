# HeadShow调教版

## 一个可以把玩家信息显示在头顶上的插件

## 配置文件
- 文件路径:plugins/HeadShow/config.json
```json
{   
    "updateTick":60,
    "scoreBoard": {
      "score": "money",
      "score1": "money1"
    },
    "showTitle":"%Name%\n§c❤§b%maxHealth%§e/§a%health% §b%maxHunger%§e/§a%hunger%\n§f%device% §c%avgPing%ms\n%score%,%score1%"
}
```
- 占位符:
    |占位符|描述|
    |:-:|:-:|
    |```%maxHealth%```|玩家最大生命值|
    |```%maxHunger%```|玩家最大饥饿值|
    |```%health%```|玩家当前生命值|
    |```%hunger%```|玩家当前饥饿值|
    |```%device%```|玩家当前的设备|
    |```%avgPing%```|玩家当前的平均Ping值|
    |```%Name%```|玩家名|
    |```%money%```|玩家的llmoney数值|
    |```%score%```|玩家scoreboard的数值(scoreboard配置在config中)|
    
## 联系方式
### Email:2351078777@qq.com

# 效果预览
![Preview](https://i.ibb.co/YcxbPNQ/024-S-Y26-XG-QAHY1-TRV.png)