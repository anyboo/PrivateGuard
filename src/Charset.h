#ifndef _CHARSET_H_
#define _CHARSET_H_

#include <string>
#include <wchar.h>

using namespace std;

class Charset
{
public:
    // ANSIתΪUnicode
    static void AnsiToUnicode(const string &src, wstring &dest);
    // UnicodeתΪANSI
    static void UnicodeToAnsi(const wstring &src, string &dest);

    // ANSIתΪUTF8
    static void AnsiToUTF8(const string &src, string &dest);
    // UTF8תΪANSI
    static void UTF8ToAnsi(const string &src, string &dest);

    // UTF8תΪUNICODE
    static void UTF8ToUnicode(const string &src, wstring &dest);
    // UNICODEתΪUTF8
    static void UnicodeToUTF8(const wstring &src, string &dest);

    // ��������
    static wstring s2ws(const string& s);
    static string ws2s(const wstring& ws);
};

#endif /* _CHARSET_H_ */ 
