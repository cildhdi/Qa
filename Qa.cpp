#include "Qa.h"

namespace Qa
{
	std::wstring StringToWideString(std::string str)
	{
		if (str.size() == 0)
		{
			return L"";
		}

		wchar_t *pszBuf = NULL;
		int needWChar = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		if (needWChar > 0)
		{
			pszBuf = new wchar_t[needWChar + 1];
			ZeroMemory(pszBuf, (needWChar + 1) * sizeof(wchar_t));
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pszBuf, needWChar);
		}
		std::wstring wStr = pszBuf;
		delete[] pszBuf;
		return wStr;
	}

	std::string WideStringToString(std::wstring wStr)
	{
		if (wStr.size() == 0)
		{
			return "";
		}

		char *pszBuf = NULL;
		int needBytes = WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, NULL, 0, NULL, NULL);
		if (needBytes > 0)
		{
			pszBuf = new char[needBytes + 1];
			ZeroMemory(pszBuf, (needBytes + 1) * sizeof(char));
			WideCharToMultiByte(CP_ACP, 0, wStr.c_str(), -1, pszBuf, needBytes, NULL, NULL);
		}
		std::string str = pszBuf;
		delete[] pszBuf;
		return str;
	}


	void match_rules::add_rule(std::wstring match_str)
	{
		match_strs.push_back(match_str);
	}

	void match_rules::clear()
	{
		match_strs.clear();
	}

	unsigned int match_rules::operator()(qsn_item& qi)
	{
		unsigned int match_result = 0;
		for (auto match_str : match_strs)
		{
			if (qi.body.find(match_str) != std::wstring::npos)
			{
				match_result++;
			}
		}
		return match_result;
	}

	std::ostream& operator<<(std::ostream& out, match_result& mr)
	{

		std::wostringstream os;
		os << std::endl << L"---------------------------------------" << std::endl;
		os << L"该题匹配数量：" << mr.match_num << std::endl;
		os << L"题目：" << mr.qi.body << std::endl;
		os << L"A." << mr.qi.A;
		os << L"    B." << mr.qi.B;
		os << L"    C." << mr.qi.C;
		os << L"    D." << mr.qi.D << std::endl;
		os << L"答案：" << mr.qi.answer << std::endl;

		out << WideStringToString(os.str());

		return out;
	}


}