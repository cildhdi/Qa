// Qa.cpp: 定义控制台应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_WCSTOK

#include <iterator>
#include "stdafx.h"
#include "Qa.h"

std::vector<std::wstring> split(std::wstring str, std::wstring pattern)
{
	std::wstring::size_type pos;
	std::vector<std::wstring> result;

	str += pattern; 
	unsigned int size = str.size();

	for (unsigned int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::wstring s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


int main()
{
	std::cout << "匹配字符串格式，从题目中选取几个(必须不少于两个)连续的一段文字，不要包括除汉字以外的字符，用减号即 - 隔开。" << std::endl;
	std::cout << "例如，有题目：" << std::endl;
	std::cout << "提高污染排放标准，强化排污者责任，健全（   ）、（   ）、（   ）等制度。" << std::endl;
	std::cout << "则可以输入：" << std::endl;
	std::cout << "提高-污染排放-排污者" << std::endl;
	std::cout << "回车后会输出匹配的题目，按匹配的数量递增排序，即越往下越可能是正确答案。" << std::endl;
	Qa::match_rules mr;
	std::wstring input_str;
	std::vector<Qa::match_result> results;
	while (true)
	{
		std::cout << std::endl << std::endl << "输入匹配字符串：" << std::endl;
		std::string str;
		std::cin >> str;
		input_str = Qa::StringToWideString(str);

		auto strs = split(input_str, L"-");

		for (auto& str : strs)
		{
			mr.add_rule(str);
		}
		Qa::match_result mre;
		for (auto& qi : Qa::datas)
		{
			mre.match_num = mr(qi);
			if (mre.match_num > 1)
			{
				mre.qi = qi;
				results.push_back(mre);
			}
		}

		std::sort(results.begin(), results.end(), [](Qa::match_result& lmr, Qa::match_result& rmr)
		{
			return lmr.match_num < rmr.match_num;
		});

		if (results.empty())
		{
			std::cout << "没有匹配的题目，请重新输入。";
		}
		else
		{
			for (auto& ret : results)
			{
				std::cout << ret;
			}
		}

		mr.clear();
		input_str.clear();
		results.clear();
	}
	system("pause");
	return 0;
}

