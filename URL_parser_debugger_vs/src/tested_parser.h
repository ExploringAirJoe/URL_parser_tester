#ifndef TESTED_PARSER_H
#define TESTED_PARSER_H

#include<string>
#include<map>
#include<regex>

#include "parsed_url.h"

ParsedURL parser_test(std::string url);//接口，使用者需要引用tested_parser.h并实现符合该格式的parse函数

#endif