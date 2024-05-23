# URL_parser_debugger

a debug tool to test URL parser

## 项目题目

编写一个URL_parser_debugger
具体内容：
URL（统一资源定位系统）是因特网的万维网服务程序上用于指定信息位置的表示方法。它是一个字符串，由协议、主机、端口、路径等部分组成。而这个字符串并不能被直接使用，需要经过一个url_parser的解析，将url所包含的各部分信息提取出来才能进一步使用。url_parser的具体实现程序各不相同，每个url_parser的编写者都需要自己编写一个针对自己的程序的测试器(debugger)。我们期望编写一个具有一定通用性的URL_parser_debugger，它可以通过某种方式与各种url_parser进行连接，并对其进行测试，从而减轻url_parser编写者的debug负担。

## 前置背景

1. URL格式规范
2. url_parser需要做的任务
  
## 主要工作

1. URL_parser_debugger需要对url_parser进行测试的内容
2. 代码实现思路
  
- 编写语言：C++
- 如何与url_parser进行连接：
  在头文件tested_parser.h中声明了函数ParsedURL parser_test(std::string url)作为接口，使用者需要根据url_parser的具体实现来实现函数parser_test，从而使用URL_parser_debugger。
- 测试思路：
  主要采取黑盒测试的手段，并结合URL格式规范，推测各种url_parser的共性，进行有一定规则的测试用例生成，以期望用尽量少的测试用例覆盖尽可能多的情况，并“猜测”边界位置进行有针对性的生成。
  测试用例分为多个层面（main函数中调用的函数）：
  - test_basic_legal_url：直接利用现有的合法url对url_parser的功能进行简单的基础测试
  - test_basic_illegal_url：利用现有的非法url对url_parser的错误反馈功能进行简单的测试
  - test_random_legal_url：根据定义的规则进行合法url的随机生成，测试url_parser的解析正确性
  - test_random_illegal_url：根据定义的规则进行非法url的随机生成，测试url_parser的错误反馈功能

