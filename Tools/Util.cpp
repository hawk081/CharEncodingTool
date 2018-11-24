#include "StdAfx.h"
#include "Util.h"

Util::Util(void)
{
}

Util::~Util(void)
{
}

CString Util::UTF82UnicodeStr(const wchar_t *szIn)
{
    std::wstring szTemp(szIn);
    CString szRet(_T(""));
    TCHAR value = 0;
    unsigned char firstchar =  0;
    unsigned char secondchar = 0;
    unsigned char thirdchar =  0;
    for (unsigned int i = 0; i < szTemp.length();)
    {
        // Check if the char is 3Byte UTF-8 
        if ((unsigned char)szTemp[i] >= 127 && (unsigned char)szTemp[i + 1] >= 127 && (unsigned char)szTemp[i + 2] >= 127)
        {
            firstchar =  (unsigned char)szTemp[i];
            secondchar = (unsigned char)szTemp[i + 1];
            thirdchar =  (unsigned char)szTemp[i + 2];
            value  = (firstchar & 0x1f)  << 12;
            value |= (secondchar & 0x3f) << 6;
            value |= (thirdchar & 0x3f);

            szRet += value;
            i += 3;
        }
        // Check if the char is 2Byte UTF-8 
        else if ((unsigned char)szTemp[i] >= 127 && (unsigned char)szTemp[i + 1] >= 127 )
        {
            firstchar =  (unsigned char)szTemp[i];
            secondchar = (unsigned char)szTemp[i + 1];

            value  = (firstchar  & 0x1f) << 6;
            value |= (secondchar & 0x3f);

            szRet += value;
            i += 2;
        }
        else
        {
            szRet += (TCHAR)szTemp[i];
            ++i;
        }
        
    }
    return szRet;
}

std::wstring Util::Unicode2UTF8(const CString szIn)
{
    std::wstring szRet(L"");
    unsigned char firstchar =  0;
    unsigned char secondchar = 0;
    unsigned char thirdchar =  0;
    TCHAR value = 0;
    for ( int i = 0; i < szIn.GetLength(); i++ )
    {
        if ( (unsigned int)szIn.GetAt(i) <= 126 )
        {
            szRet.push_back((char)szIn.GetAt(i));
        }
        // Convert to 2Byte UTF-8 
        else if ( (unsigned int)szIn.GetAt(i) >= 0x0080 && (unsigned int)szIn.GetAt(i) <= 0x07ff )
        {
            value = szIn.GetAt(i);
            firstchar = ( ( value >> 6 ) & 0xef ) | 0xc0;
            secondchar =  ( value & 0x3f ) | 0x80;
            szRet.push_back(firstchar);
            szRet.push_back(secondchar);
        }
        // Convert to 3Byte UTF-8
        else if ( (unsigned int)szIn.GetAt(i) >= 0x0800 && (unsigned int)szIn.GetAt(i) <= 0xffff )
        {
            value = szIn.GetAt(i);
            firstchar =  ( value >> 12 ) | 0xE0;
            secondchar = ( ( value >> 6 ) & 0x3f ) | 0x80;
            thirdchar =  ( value & 0x3f ) | 0x80;
            szRet.push_back(firstchar);
            szRet.push_back(secondchar);
            szRet.push_back(thirdchar);
        }
    }

    return szRet;
}

std::wstring Util::CString2string(CString UnicodeStr)
{
    std::wstring str = UnicodeStr.GetBuffer(0);

    return str;
}

long Util::String2Integer(std::wstring strInput, int _nWeight)
{
    long value = 0;
    int nWeight = _nWeight;

    for ( std::wstring::size_type i = 0;i < strInput.size(); ++i )
    {

        TCHAR t_char = strInput.at(i);
        if ( t_char >= L'0' && t_char <= L'9' )
        {
            value = (value * nWeight + ( t_char - L'0') );
        }
        else if ( t_char >= L'a' && t_char <= L'f' )
        {
            value = (value * nWeight + ( t_char - L'a' + 10 ) );
        }
        else if ( t_char >= L'A' && t_char <= L'F' )
        {
            value = (value * nWeight + ( t_char - L'A' + 10 ) );
        }
    }
    return value;
}