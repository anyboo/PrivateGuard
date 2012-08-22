#ifndef _CHARSET_H_
#define _CHARSET_H_

#include <string>
#include <wchar.h>

using namespace std;

class Charset
{
public:
    // ANSI转为Unicode
    static void AnsiToUnicode(const string &src, wstring &dest);
    // Unicode转为ANSI
    static void UnicodeToAnsi(const wstring &src, string &dest);

    // ANSI转为UTF8
    static void AnsiToUTF8(const string &src, string &dest);
    // UTF8转为ANSI
    static void UTF8ToAnsi(const string &src, string &dest);

    // UTF8转为UNICODE
    static void UTF8ToUnicode(const string &src, wstring &dest);
    // UNICODE转为UTF8
    static void UnicodeToUTF8(const wstring &src, string &dest);

    // 辅助函数
    static wstring s2ws(const string& s);
    static string ws2s(const wstring& ws);
};

#endif /* _CHARSET_H_ */ 
