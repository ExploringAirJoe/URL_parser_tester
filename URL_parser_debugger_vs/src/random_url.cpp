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
    for (int case_num = 0; case_num <= 10; case_num++)
    {
        random_protocol = generate_random_protocol(PROTOCOL_LEGAL);

        // Generate random hostname
        random_hostname = generate_random_hostname(HOSTNAME_LEGAL);

        // Generate random port
        random_port = generate_random_port(PORT_LEGAL);

        // Generate random path
        random_path = generate_random_path(PATH_LEGAL);

        // Generate random query params
        //random_query_params = (rand() % 2 == 0) ? "?param1=value1&param2=value2" : "";

        // Generate random fragment
        random_fragment = (rand() % 2 == 0) ? "section" : "";

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
            std::cout << "random legal url " << url << " is parsed successfully!" << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "random legal url " << url << " is parsed wrongly!" << std::endl;
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

//随机生成一个指定类型协议
std::string generate_random_protocol(int kind)
{
    std::string protocol;

    switch (kind)
    {
    case PROTOCOL_LEGAL:
        protocol = generate_random_string(rand() % 10 + 3);
        break;
    default:
        break;
    };

    return protocol;
}

//随机生成一个指定类型主机名
std::string generate_random_hostname(int kind)
{
    std::string hostname;

    switch (kind)
    {
    case HOSTNAME_LEGAL:
        int legal_kind;
        legal_kind = rand() % 3;//0采取域名，1采取IPv4，2采取IPv6
        switch (legal_kind)
        {
        case 0:
            int num;
            num = rand() % 4 + 1;
            for (int i = 0; i < num; i++)
            {
                if (i)hostname += ".";
                hostname += generate_random_string(rand() % 10 + 3);
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++)
            {
                if (i) hostname += ".";
                hostname += std::to_string(rand() % 256);
            }
            break;
        case 2:
            hostname = "[";
            for (int i = 0; i < 8; i++)
            {
                if (i) hostname += ".";
                hostname += std::to_string(rand() % 256);
            }
            hostname += "]";
            break;
        default:
            break;
        }
        break;
    default:
        break;
    };

    return hostname;
}

//随机生成一个指定类型端口
int generate_random_port(int kind)
{
    int port = 0;

    switch (kind)
    {
    case PORT_LEGAL:
        int legal_kind;
        legal_kind = rand() % 5;
        if (legal_kind > 0)port = rand() % 65535 + 1;
        else port = -1;
        break;
    default:
        break;
    };

    return port;
}

//随机生成一个指定类型路径
std::string generate_random_path(int kind)
{
    std::string path;

    switch (kind)
    {
    case PATH_LEGAL:
        int length;
        length = rand() % 5;
        for (int i = 0; i < length; i++)
        {
            path += "/" + generate_random_string(rand() % 10 + 3);
        }
        break;
    default:
        break;
    };

    return path;
}

//随机生成一个指定类型参数列表
std::map<std::string, std::string> generate_random_query_params(int kind)
{
    std::map<std::string, std::string> query_params;

    return query_params;
}

//随机生成一个指定类型片段
std::string generate_random_fragment(int kind)
{
    std::string fragment;

    return fragment;
}