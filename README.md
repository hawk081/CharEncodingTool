# CharEncodingTool(字符编码工具)

用于完成不同字符集字符到其其内码之间的相互转换, 例如: [Unicode](https://en.wikipedia.org/wiki/Unicode), [UTF-8](https://en.wikipedia.org/wiki/UTF-8), [Code page](https://en.wikipedia.org/wiki/Code_page)

## 支持的字符集:
* Unicode
* UTF-8
* GBK(codepage 936), 简体中文
* BIG5(codepage 950), 繁体中文
* Codepage 932, 日文字符
* Codepage 949, 韩文字符
* Codepage 874, 泰文字符

## 功能截图
### Unicode字符与其内码相互转换
* 支持\x963f, \u963f, %963f之类的输入与输出

![Unicode](https://gitee.com/hawk/CharEncodingTool/raw/master/images/unicode.gif)

### UTF-8字符与内码相互转换
* 支持\xE6\x88\x91, \uE6\u88\u91, %E6%88%91, \346\210\221作为输入与输出

![UTF-8](https://gitee.com/hawk/CharEncodingTool/raw/master/images/utf8.gif)

### 支持GBK字符与内码相互转换
* 支持\xCE\xD2, \uCE\uD2, %CE%D2, \316\322作为输入和输出

![GBK](https://gitee.com/hawk/CharEncodingTool/raw/master/images/gbk.gif)

## 预编译的可执行文件
binary/CharEncodingTool-*.exe
