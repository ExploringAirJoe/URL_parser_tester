#include <iostream>
#include <fstream>

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
    int random_port = -1;
    std::string random_path;
    std::map<std::string, std::string>random_query_params;
    std::string random_fragment;

    //普通合法url
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
        random_query_params = generate_random_query_params(QUERY_PARAMS_LEGAL);

        // Generate random fragment
        random_fragment = generate_random_fragment(FRAGMENT_LEGAL);

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
            std::cout << "random legal url " << url << " is parsed "
                << "\033[32m" << "successfully!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "random legal url " << url << " is parsed"
                << "\033[31m" << " wrongly!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
    }

    //强化合法url
    for (int case_num = 0; case_num <= 10; case_num++)
    {
        random_protocol = generate_random_protocol(PROTOCOL_STRONG_LEGAL);

        // Generate random hostname
        random_hostname = generate_random_hostname(HOSTNAME_STRONG_LEGAL);

        // Generate random port
        random_port = generate_random_port(PORT_STRONG_LEGAL);

        // Generate random path
        random_path = generate_random_path(PATH_STRONG_LEGAL);

        // Generate random query params
        random_query_params = generate_random_query_params(QUERY_PARAMS_STRONG_LEGAL);

        // Generate random fragment
        random_fragment = generate_random_fragment(FRAGMENT_STRONG_LEGAL);

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
            std::cout << "random legal url " << url << " is parsed "
                << "\033[32m" << "successfully!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "random legal url " << url << " is parsed"
                << "\033[31m" << " wrongly!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
    }
}

//测试随机非法url
void test_random_illegal_url()
{
    ParsedURL refer_parsed_url;
    ParsedURL parsed_url;
    std::string url;

    //多次随机生成
    for (int case_num = 0; case_num <= 10; case_num++)
    {
        // Generate random illegal url
        url = generate_random_illegal_url();

        parsed_url = parser_test(url);
        bool parse_correct = compare_parsed_url(refer_parsed_url,parsed_url);//比较结果
        //结果正确
        if (parse_correct)
        {
            std::cout << "random illegal url " << url << " is parsed "
                << "\033[32m" << "successfully!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
        //结果错误
        else
        {
            std::cout << "random illegal url " << url << " is parsed"
                << "\033[31m" << " wrongly!" << "\033[0m" << std::endl << std::endl << std::endl;
        }
    }
}

//随机生成一个指定类型非法url
std::string generate_random_illegal_url()
{
    std::string url;
    int total_error = 0;
    bool is_wrong = false;

    // Generate random illegal protocol
    is_wrong = rand() % 2;
    total_error += is_wrong;
    std::string random_protocol = generate_random_protocol(is_wrong);

    // Generate random illegal hostname
    is_wrong = rand() % 2;
    total_error += is_wrong;
    std::string random_hostname = generate_random_hostname(is_wrong);

    // Generate random illegal port
    is_wrong = rand() % 2;
    total_error += is_wrong;
    int random_port = generate_random_port(is_wrong);

    // Generate random illegal path
    is_wrong = rand() % 2;
    total_error += is_wrong;
    std::string random_path = generate_random_path(is_wrong);

    // Generate random illegal query params
    is_wrong = rand() % 2;
    total_error += is_wrong;
    std::map<std::string, std::string> random_query_params = generate_random_query_params(is_wrong);

    // Generate random illegal fragment
    is_wrong = rand() % 2;
    total_error += is_wrong;
    std::string random_fragment = generate_random_fragment(is_wrong);

    // Construct the illegal url
    url = random_protocol;
    if (total_error)
    {
        url+=(rand() % 7 ? "://" : ":/");
    }
    else
    {
        url += (rand() % 2 ? "" : ":////");
    }
    url += random_hostname + ":" + std::to_string(random_port) + random_path;

    if (!random_query_params.empty()) {
        url += "?";
        for (auto it = random_query_params.begin(); it != random_query_params.end(); ++it) {
            url += url_encode(it->first) + "=" + url_encode(it->second);
            if (std::next(it) != random_query_params.end()) {
                url += "&";
            }
        }
    }

    if (!random_fragment.empty())
    {
        url += "#" + random_fragment;
    }

    return url;
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

//随机生成长度为length的字符串，包括字母数字和保留字符
std::string generate_random_strong_string(int length)
{
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const std::string special_charset = "%/.#?;:$+@&={}|\\^~[]'<>";
    std::string result;
    for (int i = 0; i < length; ++i) {
        if (rand() % 2)
        {
            result.push_back(charset[rand() % charset.length()]);
        }
        else
        {
            result.push_back(special_charset[rand() % special_charset.length()]);
        }
    }
    return result;
}


//随机生成一个指定类型协议
std::string generate_random_protocol(int kind)
{
    std::string protocol;
    const std::string legal_protocol[] = { "file","http","https","FTP","gopher","mailto","MMS",
        "ed2k","Flashget","thunder","tel","sms"};

    switch (kind)
    {
    case PROTOCOL_LEGAL:
        protocol = legal_protocol[rand() % legal_protocol->length()];
        break;
    case PROTOCOL_ILLEGAL:
        protocol = "";
        break;
    case PROTOCOL_STRONG_LEGAL:
        protocol = generate_random_string(rand() % 20 + 1);
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
    case HOSTNAME_ILLEGAL:
        int illegal_kind;
        illegal_kind = rand() % 3;//0采取空串，1采取非法字符(空格)，2采取非法长度
        switch (illegal_kind)
        {
        case 0:
            hostname = "";
            break;
        case 1:
            hostname = generate_random_string(rand() % 10 + 3);
            hostname.insert(rand() % hostname.length(), " ");
            break;
        case 2:
            hostname = generate_random_string(rand() % 255 + 256);
            break;
        default:
            break;
        }
        break;
    case HOSTNAME_STRONG_LEGAL:
        int strong_legal_kind;
        strong_legal_kind = rand() % 3;//0采取域名，1采取IPv4，2采取IPv6
        switch (strong_legal_kind)
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
        if (legal_kind > 0) port = rand() % 2048 + 1;
        else port = -1;
        break;
    case PORT_ILLEGAL:
        int illegal_kind;
        illegal_kind = rand() % 2;//0采取0，1采取非法端口
        switch (illegal_kind)
        {
        case 0:
            port = 0;
            break;
        case 1:
            port = rand() % 65536 + 65536;
            break;
        default:
            break;
        }
        break;
    case PORT_STRONG_LEGAL:
        int strong_legal_kind;
        strong_legal_kind = rand() % 5;
        if (strong_legal_kind > 0) port = rand() % 65535 + 1;
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
    int length;

    switch (kind)
    {
    case PATH_LEGAL:
        length = rand() % 5;
        for (int i = 0; i < length; i++)
        {
            path += "/" + generate_random_string(rand() % 10 + 3);
        }
        break;
    case PATH_ILLEGAL:
        length = rand() % 5 + 1;
        for (int i = 0; i < length; i++)
        {
            path += "/" + generate_random_string(rand() % 10);
        }
        path.insert(rand() % path.length(), " ");
        break;
    case PATH_STRONG_LEGAL:
        length = rand() % 5;
        for (int i = 0; i < length; i++)
        {
            path += "/" + generate_random_string(rand() % 10 + 1);
        }
        if ((length == 0) && (rand() % 2 == 0))
        {
            path = "/";
        }
    default:
        break;
    };

    return path;
}

//随机生成一个指定类型参数列表
std::map<std::string, std::string> generate_random_query_params(int kind)
{
    std::map<std::string, std::string> query_params;

    std::string param;
    std::string value;
    int count;

    switch (kind)
    {
    case QUERY_PARAMS_LEGAL:
        count = rand() % 6;
        
        for (int i = 0; i < count; i++)
        {
            param = generate_random_string(rand() % 8 + 2);
            value = generate_random_string(rand() % 8 + 2);
            query_params[param] = value;
        }
        break;
    case QUERY_PARAMS_ILLEGAL:
        count = rand() % 6;
        
        for (int i = 0; i < count; i++)
        {
            param = generate_random_string(rand() % 8 + 2);
            value = "";
            query_params[param] = value;
        }
        break;
    case QUERY_PARAMS_STRONG_LEGAL:
        count = rand() % 6;

        for (int i = 0; i < count; i++)
        {
            param = generate_random_string(rand() % 10 + 1);
            value = generate_random_strong_string(rand() % 10 + 0);
            query_params[param] = value;
        }
        break;
    default:
        break;
    };

    return query_params;
}

//随机生成一个指定类型片段
std::string generate_random_fragment(int kind)
{
    std::string fragment;

    switch (kind)
    {
    case FRAGMENT_LEGAL:
        fragment = generate_random_string(rand() % 5);
        break;
    case FRAGMENT_ILLEGAL:
        fragment = generate_random_string(rand() % 5 + 1);
        fragment.insert(rand() % fragment.length(), " ");
        break;
    case FRAGMENT_STRONG_LEGAL:
        fragment = generate_random_strong_string(rand() % 30);
        break;
    default:
        break;
    };

    return fragment;
}