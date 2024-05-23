#include <nlohmann/json.hpp>

#include "parsed_url.h"

#include "tested_parser.h"
#include "basic_url.h"
#include "random_url.h"

int main()
{
	//初始化种子，服务于随机化测试
	srand((unsigned int)time(NULL));

	//测试基础合法url
	test_basic_legal_url();

	//测试基础非法url
	test_basic_illegal_url();

	//测试随机合法url
	test_random_legal_url();

	//测试随机非法url
	test_random_illegal_url();
	
	return 0;
}