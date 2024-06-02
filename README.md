# URL_parser_tester: a test tool for URL parser

## 编写一个URL_parser_tester

URL（统一资源定位系统）是因特网的万维网服务程序上用于指定信息位置的表示方法。它是一个字符串，由协议、主机、端口、路径等部分组成。而这个字符串并不能被直接使用，需要经过一个`url_parser`的解析，将url所包含的各部分信息提取出来才能进一步使用。`url_parser`的具体实现程序各不相同，每个`url_parser`的编写者都需要自己编写一个针对自己的程序的测试器(`tester`)。我们期望编写一个具有一定通用性的`URL_parser_tester`，它可以通过某种方式与各种`url_parser`进行连接，并对其进行测试，从而减轻`url_parser`编写者的debug负担。

## 前置背景

1. URL格式规范
2. `url_parser`需要做的任务
  
## 主要工作

1. `URL_parser_tester`需要对`url_parser`进行测试的内容

   - url成分的正确分割
   - 对特殊字符的正确解析
   - 对非法url的正确识别
  
2. 代码实现思路
  
   - 编写语言：C++
   - 如何与`url_parser`进行连接：
     在头文件tested_parser.h中声明了函数`ParsedURL parser_test(std::string url)`作为接口，使用者需要根据`url_parser`的具体实现来实现函数`parser_test`，从而使用`URL_parser_tester`。
   - 测试思路：
     主要采取黑盒测试的手段，并结合URL格式规范，推测各种url_parser的共性，进行有一定规则的测试用例生成，以期望用尽量少的测试用例覆盖尽可能多的情况，并“猜测”边界位置进行有针对性的生成。
     测试用例分为多个层面（main函数中调用的函数）：
     - `test_basic_legal_url`：直接利用现有的合法url对`url_parser`的功能进行简单的基础测试和更靠近边界的强化测试
     - `test_basic_illegal_url`：利用现有的非法url对`url_parser`的错误反馈功能进行简单的测试
     - `test_random_legal_url`：根据定义的规则进行一些简单合法url和更靠近边界的强化合法url的随机生成，测试`url_parser`的解析正确性
     - `test_random_illegal_url`：根据定义的规则进行非法url的随机生成，测试`url_parser`的错误反馈功能

3. 测试结果
  
   将测试次数设为 $10000$，得到如下结果：

   | basic legal url | basic illegal url |
   | --------------- | ----------------- |
   |      8/12       |       16/17       |

   | random legal url | random illegal url |
   | ---------------- | ------------------ |
   |    2616/20000    |     5731/10000     |
   |    2515/20000    |     5825/10000     |
   |    2529/20000    |     5716/10000     |
   |    2587/20000    |     5789/10000     |
   |    2503/20000    |     5872/10000     |
   |    2522/20000    |     5743/10000     |
   |    2511/20000    |     5781/10000     |
   |    2540/20000    |     5686/10000     |
   |    2578/20000    |     5631/10000     |
   |    2527/20000    |     5830/10000     |
