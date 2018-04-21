#pragma once
#ifndef _QA_H_
#define _QA_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <windows.h>


namespace Qa
{
	std::wstring StringToWideString(std::string str);

	std::string WideStringToString(std::wstring wStr);

	typedef struct
	{
		std::wstring body;
		std::wstring A;
		std::wstring B;
		std::wstring C;
		std::wstring D;
		std::wstring answer;
	}qsn_item;

	class match_rules
	{
	private:
		std::vector<std::wstring> match_strs;
	public:
		void add_rule(std::wstring match_str);
		void clear();
		unsigned int operator()(qsn_item& qi);
	};

	struct match_result
	{
		qsn_item qi;
		unsigned int match_num;
	};

	std::ostream& operator<<(std::ostream& out, match_result& mr);

}

#endif