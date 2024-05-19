#ifndef RANDOM_URL_H
#define RANDOM_URL_H

#include "parsed_url.h"
#include "tested_parser.h"

//分别标定了各个部分随机生成的类型
#define PROTOCOL_LEGAL 1

#define HOSTNAME_LEGAL 1

#define PORT_LEGAL 1

#define PATH_LEGAL 1

#define QUERY_PARAMS_LEGAL 1

#define FRAGMENT_LEGAL 1

void test_random_legal_url();//测试随机合法url

void test_random_illegal_url();//测试随机非法url

std::string generate_random_string(int length);//随机生成长度为length的字符串，以大小写字母和数字为字符集

std::string generate_random_protocol(int kind);//随机生成一个指定类型协议

std::string generate_random_hostname(int kind);//随机生成一个指定类型主机名

int generate_random_port(int kind);//随机生成一个指定类型端口

std::string generate_random_path(int kind);//随机生成一个指定类型路径

std::map<std::string, std::string> generate_random_query_params(int kind);//随机生成一个指定类型参数列表

std::string generate_random_fragment(int kind);//随机生成一个指定类型片段

#endif