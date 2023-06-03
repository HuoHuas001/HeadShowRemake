#pragma once
#include <string>
#include <unordered_map>

using std::string;

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
