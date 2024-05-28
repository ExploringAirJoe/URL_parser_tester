#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

#include "parsed_url.h"

using json = nlohmann::json;

//读取JSON文件中的已解析URL数据，并返回一个ParsedURL对象
ParsedURL read_parsed_url(const json& parsed_url_json)
{
    ParsedURL parsed_url;
    parsed_url.protocol = parsed_url_json["protocol"].get<std::string>();
    parsed_url.hostname = parsed_url_json["hostname"].get<std::string>();
    parsed_url.port = parsed_url_json["port"].is_null() ? -1 : parsed_url_json["port"].get<int>();
    parsed_url.path = parsed_url_json["path"].get<std::string>();
    parsed_url.query_params = parsed_url_json["query_params"].get<std::map<std::string, std::string>>();
    parsed_url.fragment = parsed_url_json["fragment"].get<std::string>();
    return parsed_url;
}

//比较参考结果和URL解析器结果
bool compare_parsed_url(const ParsedURL& refer_parsed_url, const ParsedURL& parsed_url)
{
    bool correct = true;

    //协议
    if (refer_parsed_url.protocol != parsed_url.protocol)
    {
        correct = false;
        std::cout << "\033[34m" << "[" << "\033[33m" << "protocol" << "\033[34m" << "]" << "\033[0m" << "should be"
            << "\033[34m" << "{" << "\033[33m" << refer_parsed_url.protocol << "\033[34m" << "}" << "\033[0m" << ", but your is"
            << "\033[34m" << "{" << "\033[33m" << parsed_url.protocol << "\033[34m" << "}" << "\033[0m" << std::endl;
    }

    //主机
    if (refer_parsed_url.hostname != parsed_url.hostname)
    {
        correct = false;
        std::cout << "\033[34m" << "[" << "\033[33m" << "hostname" << "\033[34m" << "]" << "\033[0m" << "should be"
            << "\033[34m" << "{" << "\033[33m" << refer_parsed_url.hostname << "\033[34m" << "}" << "\033[0m" << ", but your is"
            << "\033[34m" << "{" << "\033[33m" << parsed_url.hostname << "\033[34m" << "}" << "\033[0m" << std::endl;
    }

    //端口
    if ((refer_parsed_url.port != parsed_url.port))
    {
        correct = false;
        std::cout << "\033[34m" << "[" << "\033[33m" << "port" << "\033[34m" << "]" << "\033[0m" << "should be"
            << "\033[34m" << "{" << "\033[33m" << refer_parsed_url.port << "\033[34m" << "}" << "\033[0m" << ", but your is"
            << "\033[34m" << "{" << "\033[33m" << parsed_url.port << "\033[34m" << "}" << "\033[0m" << std::endl;
    }

    //路径
    if (refer_parsed_url.path != parsed_url.path)
    {
        if ((refer_parsed_url.path != "") || (parsed_url.path != "/"))
        {
            correct = false;
            std::cout << "\033[34m" << "[" << "\033[33m" << "path" << "\033[34m" << "]" << "\033[0m" << "should be"
                << "\033[34m" << "{" << "\033[33m" << refer_parsed_url.path << "\033[34m" << "}" << "\033[0m" << ", but your is"
                << "\033[34m" << "{" << "\033[33m" << parsed_url.path << "\033[34m" << "}" << "\033[0m" << std::endl;
        }
    }

    //参数
    if (refer_parsed_url.query_params != parsed_url.query_params)
    {
        correct = false;
        std::cout << "\033[34m" << "[" << "\033[33m" << "query_params" << "\033[34m" << "]" << "\033[0m" << "should be" << std::endl;
        for (auto it = refer_parsed_url.query_params.begin(); it != refer_parsed_url.query_params.end(); ++it)
        {
            std::cout << "    " << "key: " << "\033[33m" << it->first << "\033[0m"
                << "    value: " << "\033[33m" << it->second << "\033[0m" << std::endl;
        }
        std::cout << "    but your is:" << std::endl;
        for (auto it = parsed_url.query_params.begin(); it != parsed_url.query_params.end(); ++it)
        {
            std::cout << "    " << "key: " << "\033[33m" << it->first << "\033[0m"
                << "    value: " << "\033[33m" << it->second << "\033[0m" << std::endl;
        }
    }

    //片段
    if (refer_parsed_url.fragment != parsed_url.fragment)
    {
        correct = false;
        std::cout << "\033[34m" << "[" << "\033[33m" << "fragment" << "\033[34m" << "]" << "\033[0m" << "should be"
            << "\033[34m" << "{" << "\033[33m" << refer_parsed_url.fragment << "\033[34m" << "}" << "\033[0m" << ", but your is"
            << "\033[34m" << "{" << "\033[33m" << parsed_url.fragment << "\033[34m" << "}" << "\033[0m" << std::endl;
    }

    return correct;
}

//将字符串进行url编码
std::string url_encode(const std::string& value)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (auto&& ch : value) {
        // Keep alphanumeric and other accepted characters unchanged
        if (std::isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
            escaped << ch;
        }
        else if (ch == ' ') { // Encode space as %20
            escaped << '%' << std::setw(2) << int((unsigned char)ch);
        }
        else { // Any other characters are percent-encoded
            escaped << std::uppercase;
            escaped << '%' << std::setw(2) << int((unsigned char)ch);
            escaped << std::nouppercase;
        }
    }

    return escaped.str();
}

//将已解析的url组装为完整url
std::string ParsedURL_to_url(ParsedURL& parsed_url)
{
    std::string url;

    // Add protocol
    url += parsed_url.protocol;

    // Special handling for 'file' protocol
    if (parsed_url.protocol == "file") {
        url += ":///";
    }
    else {
        url += ":";
        int cnt = rand() % 3;
        for (int i = 0; i < cnt; i++)
        {
            url += "/";
        }
    }

    // Add hostname
    url += parsed_url.hostname;

    // Add port if it's specified and not the default for the protocol
    if (parsed_url.port > 0) {
        url += ":" + std::to_string(parsed_url.port);
    }

    // Add path (encoded)
    url += parsed_url.path;

    // Add query parameters if any
    if (!parsed_url.query_params.empty()) {
        url += "?";
        for (auto it = parsed_url.query_params.begin(); it != parsed_url.query_params.end(); ++it) {
            url += url_encode(it->first) + "=" + url_encode(it->second);
            if (std::next(it) != parsed_url.query_params.end()) {
                url += "&";
            }
        }
    }

    // Add fragment if it's specified
    if (!parsed_url.fragment.empty()) {
        url += "#" + url_encode(parsed_url.fragment);
    }

    return url;
}