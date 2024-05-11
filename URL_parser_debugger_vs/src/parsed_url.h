#ifndef PARSED_URL_H
#define PARSED_URL_H

struct ParsedURL
{
    std::string protocol;
    std::string hostname;
    int port;
    std::string path;
    std::map<std::string, std::string> query_params;
    std::string fragment;
};

#endif