#pragma once

class Util
{
public:
    Util(void);
    ~Util(void);

public:
    static CString UTF82UnicodeStr(const wchar_t *szIn);
    static std::wstring Unicode2UTF8(const CString szIn);
    static std::wstring CString2string(CString UnicodeStr);
    static long String2Integer(std::wstring strInput, int _nWeight);
};
