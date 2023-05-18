#include "BaseLib.h"


string m_replace(string strSrc,
	const string& oldStr, const string& newStr, int count)
{
	string strRet = strSrc;
	size_t pos = 0;
	int l_count = 0;
	if (-1 == count) // replace all
		count = strRet.size();
	while ((pos = strRet.find(oldStr, pos)) != string::npos)
	{
		strRet.replace(pos, oldStr.size(), newStr);
		if (++l_count >= count) break;
		pos += newStr.size();
	}
	return strRet;
}

string forEachReplace(std::unordered_map<string, string> d, string s) {
	for (auto& i : d) {
		s = m_replace(s, i.first, i.second);
	}
	return s;
}

