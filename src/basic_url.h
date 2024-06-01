#ifndef BASIC_URL_H
#define BASIC_URL_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "parsed_url.h"
#include "tested_parser.h"

using json = nlohmann::json;

std::pair<int, int> test_basic_legal_url();//测试基础合法url

std::pair<int, int> test_basic_illegal_url();//测试基础非法url

#endif