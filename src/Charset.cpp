#include "StdAfx.h"
#include <windows.h>
#include "charset.h"

// // ANSIתΪUnicode
void Charset::AnsiToUnicode(const string &src, wstring &dest)
{
    int length = MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, NULL, 0);
    wchar_t *buf = new wchar_t[length + 1];
    MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, buf, length);
    buf[length] = L'\0';
    dest = buf;
    delete [] buf;
}

// UnicodeתΪANSI
void Charset::UnicodeToAnsi(const wstring &src, string &dest)
{
    int length = WideCharToMultiByte(CP_ACP, 0, src.c_str(), 
                                     -1, NULL, 0, NULL, FALSE);
    char *buf = new char[length + 1];
    WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, buf, length, NULL, FALSE);
    buf[length] = '\0';
    dest = buf;
    delete [] buf;
}

// ANSIתΪUTF8
void Charset::AnsiToUTF8(const string &src, string &dest)
{
    wstring unicode;
    AnsiToUnicode(src, unicode);
    UnicodeToUTF8(unicode, dest);
}
// UTF8תΪANSI
void Charset::UTF8ToAnsi(const string &src, string &dest)
{
    wstring unicode;
    UTF8ToUnicode(src, unicode);
    UnicodeToAnsi(unicode, dest);
}

// UTF8תΪUNICODE
void Charset::UTF8ToUnicode(const string &src, wstring &dest)
{
    int length = MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, NULL, 0);
    wchar_t *buf = new wchar_t[length + 1];
    MultiByteToWideChar(CP_UTF8, 0, src.c_str(), -1, buf, length);
    buf[length] = L'\0';
    dest = buf;
    delete [] buf;
}
// UNICODEתΪUTF8
void Charset::UnicodeToUTF8(const wstring &src, string &dest)
{
    int length = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), 
        -1, NULL, 0, NULL, FALSE);
    char *buf = new char[length + 1];
    WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, buf, length, NULL, FALSE);
    buf[length] = '\0';
    dest = buf;
    delete [] buf;
}

// static 
wstring Charset::s2ws(const string& s)
{
    wstring ws;
    AnsiToUnicode(s, ws);
    return ws;
}

// static 
string Charset::ws2s(const wstring& ws)
{
    string s;
    UnicodeToAnsi(ws, s);
    return s;
}