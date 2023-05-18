#pragma once
#include "LLMoney.h"
#include <string>
#include <unordered_map>

using std::string;

// 定义Money类型
typedef money_t (*LLMoneyGet_T)(xuid_t);
typedef string (*LLMoneyGetHist_T)(xuid_t, int);
typedef bool (*LLMoneyTrans_T)(xuid_t, xuid_t, money_t, string const &);
typedef bool (*LLMoneySet_T)(xuid_t, money_t);
typedef bool (*LLMoneyAdd_T)(xuid_t, money_t);
typedef bool (*LLMoneyReduce_T)(xuid_t, money_t);
typedef void (*LLMoneyClearHist_T)(int);

struct dynamicSymbolsMap_type
{
    LLMoneyGet_T LLMoneyGet = nullptr;
    LLMoneySet_T LLMoneySet = nullptr;
    LLMoneyAdd_T LLMoneyAdd = nullptr;
    LLMoneyReduce_T LLMoneyReduce = nullptr;
    LLMoneyTrans_T LLMoneyTrans = nullptr;
    LLMoneyGetHist_T LLMoneyGetHist = nullptr;
    LLMoneyClearHist_T LLMoneyClearHist = nullptr;
} ;

string forEachReplace(
    std::unordered_map<string, string> d, 
    string s
    );
string m_replace(
    string strSrc,
	const string& oldStr, 
    const string& newStr, 
    int count = -1
    );
