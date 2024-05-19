//这是一个简单的url_parser实现，目的在于检验URL_parser_debugger是否能够起作用

#include "tested_parser.h"

//接口的实现
ParsedURL parser_test(std::string url)
{
    ParsedURL parsed_url;

    //简单的正则表达式解析
    std::regex url_regex(R"(([^:/?#]+):\/\/([^:/?#]*)(?::(\d+))?([^?#]*)(?:\?([^#]*))?(?:#(.*))?)");

    std::smatch url_match;
    if (std::regex_match(url, url_match, url_regex)) {
        parsed_url.protocol = url_match[1];
        parsed_url.hostname = url_match[2];

        if (url_match[3].matched)
            parsed_url.port = std::stoi(url_match[3]);
        else
            parsed_url.port = -1;

        parsed_url.path = url_match[4];

        // Parse query parameters
        std::regex param_regex(R"(([^&=]+)=([^&]+))");
        auto query_str = url_match[5];
        for (std::sregex_iterator it(query_str.first, query_str.second, param_regex), end; it != end; ++it) {
            parsed_url.query_params[(*it)[1]] = (*it)[2];
        }

        parsed_url.fragment = url_match[6];
    }

    return parsed_url;
}