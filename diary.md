 - 有关parser输出的问题
parser应当输出如下结构体：
struct ParsedURL
{
    std::string protocol;
    std::string hostname;
    int port;
    std::string path;
    std::map<std::string, std::string> query_params;
    std::string fragment;
};
其中，每个变量都有一些初始值：
类型为string的变量protocol hostname path fragment默认值为空字符串（注意，如果url中路径为空，则path中空字符串和“/”是等价的）
类型为int的变量port默认值为-1
类型为map<string,string>的变量query_params默认值为空
如果url在解析过程中发现是错误的，则应当返回一个值全为默认的结构体

 - 有关随机生成合法url的结构问题
在parsed_url.cpp文件中定义了函数std::string ParsedURL_to_url(ParsedURL& parsed_url)，它将执行如下流程：
1.直接以protocol为开头，如果协议为file则跟上:///，否则跟上://
2.加上hostname
3.在port大于零的情况下加上:port
4.加上path
5.在query_params不为空的情况下，先跟一个?，然后以“key:value”的形式依次输出各个参数并用“&”分隔（注意key和value要用url_encode函数进行处理）
6.在fragment不为空的情况下，先加一个#，然后加上fragment