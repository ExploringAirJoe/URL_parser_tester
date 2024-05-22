#include<iostream>
#include<fstream>
#include<nlohmann/json.hpp>

#include "basic_url.h"

using json = nlohmann::json;

//测试基础合法url
void test_basic_legal_url()
{
    //文件流读取基础合法url的JSON文件数据
	std::ifstream file("../../../basic_url/basic_legal_url.json");
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
	json basic_legal_url;
	file >> basic_legal_url;
    file.close();

    for (json::iterator it = basic_legal_url.begin(); it != basic_legal_url.end(); ++it)
    {
        std::string test_case_name = it.key();
        json test_case_data = it.value();

        std::string url = test_case_data["url"];
        ParsedURL refer_parsed_url = read_parsed_url(test_case_data["parsed_url"]);//参照结果
        ParsedURL parsed_url = parser_test(url);//URL解析器结果
        
        bool parse_correct = compare_parsed_url(refer_parsed_url, parsed_url);//比较结果
        //结果正确
        if (parse_correct)
        {
            std::cout << "basic legal url " << url << " is parsed successfully!" << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "basic legal url " << url << " is parsed wrongly!" << std::endl;
        }
    }
}

//测试基础非法url
void test_basic_illegal_url()
{
    //文件流读取基础合法url的JSON文件数据
    std::ifstream file("../../../basic_url/basic_illegal_url.json");
    json basic_legal_url;
    file >> basic_legal_url;

    for (json::iterator it = basic_legal_url.begin(); it != basic_legal_url.end(); ++it) {
        std::string test_case_name = it.key();
        json test_case_data = it.value();

        std::string url = test_case_data["url"];
        ParsedURL refer_parsed_url;//参照结果
        refer_parsed_url.protocol = "";
        refer_parsed_url.hostname = "";
        refer_parsed_url.path = "";
        refer_parsed_url.port = -1;
        refer_parsed_url.fragment = "";

        ParsedURL parsed_url = parser_test(url);//URL解析器结果

        bool parse_correct = compare_parsed_url(refer_parsed_url, parsed_url);//比较结果
        //结果正确
        if (parse_correct)
        {
            std::cout << "basic illegal url " << url << " is parsed successfully!" << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "basic illegal url " << url << " is parsed wrongly!" << std::endl;
        }
    }
}