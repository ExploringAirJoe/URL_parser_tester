#include <iostream>
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
	std::cout << "\033[33m" << "Now testing basic legal url!" << "\033[0m" << std::endl << std::endl << std::endl;
	std::pair<int, int> blp = test_basic_legal_url();
	std::cout << "\033[34m" << "[" << "\033[33m" << blp.first << "\033[34m" << "/" << "\033[33m" << blp.second << "\033[34m" << "]" << "\033[0m" << " cases passed." << std::endl << std::endl;

	//测试基础非法url
	std::cout << "\033[33m" << "Now testing basic illegal url!" << "\033[0m" << std::endl << std::endl << std::endl;
	std::pair<int, int> bip = test_basic_illegal_url();
	std::cout << "\033[34m" << "[" << "\033[33m" << bip.first << "\033[34m" << "/" << "\033[33m" << bip.second << "\033[34m" << "]" << "\033[0m" << " cases passed." << std::endl << std::endl;

	//测试随机合法url
	std::cout << "\033[33m" << "Now testing random legal url!" << "\033[0m" << std::endl << std::endl << std::endl;
	std::pair<int, int> rlp = test_random_legal_url();
	std::cout << "\033[34m" << "[" << "\033[33m" << rlp.first << "\033[34m" << "/" << "\033[33m" << rlp.second << "\033[34m" << "]" << "\033[0m" << " cases passed." << std::endl << std::endl;

	//测试随机非法url
	std::cout << "\033[33m" << "Now testing random illegal url!" << "\033[0m" << std::endl << std::endl << std::endl;
	std::pair<int, int> rip = test_random_illegal_url();
	std::cout << "\033[34m" << "[" << "\033[33m" << rip.first << "\033[34m" << "/" << "\033[33m" << rip.second << "\033[34m" << "]" << "\033[0m" << " cases passed." << std::endl << std::endl;
	
	std::cout << "for basic legal url, " << "\033[34m" << blp.first << "\033[33m" << "/" << "\033[34m" << blp.second << "\033[0m" << " cases passed." << std::endl;
	std::cout << "for basic illegal url, " << "\033[34m" << bip.first << "\033[33m" << "/" << "\033[34m" << bip.second << "\033[0m" << " cases passed." << std::endl;
	std::cout << "for random legal url, " << "\033[34m" << rlp.first << "\033[33m" << "/" << "\033[34m" << rlp.second << "\033[0m" << " cases passed." << std::endl;
	std::cout << "for random illegal url, " << "\033[34m" << rip.first << "\033[33m" << "/" << "\033[34m" << rip.second << "\033[0m" << " cases passed." << std::endl;

	return 0;
}