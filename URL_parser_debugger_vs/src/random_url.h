#ifndef RANDOM_URL_H
#define RANDOM_URL_H

#include "parsed_url.h"
#include "tested_parser.h"



void test_random_legal_url();//测试随机合法url

void test_random_illegal_url();//测试随机非法url

std::string generate_random_string(int length);//随机生成长度为length的字符串，以大小写字母和数字为字符集

#endif