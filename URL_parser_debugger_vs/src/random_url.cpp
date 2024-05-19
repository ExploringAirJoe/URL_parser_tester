#include<iostream>
#include<fstream>

#include "random_url.h"

/*
struct ParsedURL
{
    std::string protocol;
    std::string hostname;
    int port = 0;
    std::string path;
    std::map<std::string, std::string> query_params;
    std::string fragment;
};
*/

//测试随机合法url
void test_random_legal_url()
{
	ParsedURL refer_parsed_url;
    ParsedURL parsed_url;
    std::string url;

    //随机生成的各部分
    std::string random_protocol;
    std::string random_hostname;
    int random_port = 0;
    std::string random_path;
    std::map<std::string, std::string>random_query_params;
    std::string random_fragment;

    //多次随机生成
    for (int case_num = 0; case_num <= 10; case_num)
    {
        random_protocol = (rand() % 2 == 0) ? "http" : "https";

        // Generate random hostname
        random_hostname = generate_random_string(10) + ".com";

        // Generate random port
        random_port = (rand() % 10000) + 1;

        // Generate random path
        random_path = "/" + generate_random_string(10);

        // Generate random query params
        //random_query_params = (rand() % 2 == 0) ? "?param1=value1&param2=value2" : "";

        // Generate random fragment
        random_fragment = (rand() % 2 == 0) ? "#section" : "";

        //对refer_parsed_url进行赋值
        refer_parsed_url.protocol = random_protocol;
        refer_parsed_url.hostname = random_hostname;
        refer_parsed_url.port = random_port;
        refer_parsed_url.path = random_path;
        refer_parsed_url.query_params = random_query_params;
        refer_parsed_url.fragment = random_fragment;
        
        //将refer_parsed_url转化为url
        url = ParsedURL_to_url(refer_parsed_url);

        parsed_url = parser_test(url);
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

//测试随机非法url
void test_random_illegal_url()
{

}

//随机生成长度为length的字符串，以大小写字母和数字为字符集
std::string generate_random_string(int length)
{
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string result;
    for (int i = 0; i < length; ++i) {
        result.push_back(charset[rand() % charset.length()]);
    }
    return result;
}