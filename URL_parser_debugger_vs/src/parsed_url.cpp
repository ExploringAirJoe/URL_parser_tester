#include<iostream>
#include<fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include<nlohmann/json.hpp>

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
    }

    //主机
    if (refer_parsed_url.hostname != parsed_url.hostname)
    {
        correct = false;
    }

    //端口
    if ((refer_parsed_url.port != parsed_url.port))
    {
        correct = false;
    }

    //路径
    if (refer_parsed_url.path != parsed_url.path)
    {
        correct = false;
    }

    //参数
    if (refer_parsed_url.query_params != parsed_url.query_params)
    {
        correct = false;
    }

    //片段
    if (refer_parsed_url.fragment != parsed_url.fragment)
    {
        correct = false;
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
        url += "://";
    }

    // Add hostname
    url += parsed_url.hostname;

    // Add port if it's specified and not the default for the protocol
    if (parsed_url.port != 0) {
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