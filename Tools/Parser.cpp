#include "StdAfx.h"
#include "Parser.h"

Parser::Parser(void)
{
}

Parser::~Parser(void)
{
}

Parser::Parser(std::wstring OriginalString, EncodingType OriEType)
{
    mEncodingType = OriEType;
    mOriginalString = OriginalString;
    switch (mEncodingType)
    {
    case ENC_UTF8:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_UTF_8);
        break;
    case ENC_GBK:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_GBK);
        break;
    case ENC_BIG5:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_BIG5);
        break;
    case ENC_JPN:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_JPN);
        break;
    case ENC_KOR:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_KOR);
        break;
    case ENC_THAI:
        mParsedString = UTF8Nor2Unicode(OriginalString, Utils::CP_THAI);
        break;
    case ENC_UNICODE:
    default:
        mParsedString = OriginalString;
        mParsedString = UnicodeNor2Unicode(OriginalString);
        break;
    }
}

Parser::Parser(std::string OriginalString, EncodingType OriEType)
{
    Parser(Utils::ASCIICopy<std::wstring>(OriginalString), OriEType);
}

std::wstring Parser::_oct2_x(boost::match_results<std::wstring::const_iterator> match) const
{
    int x = 1;
    std::wstring _1 = match[1];
    long number = Utils::string2numberEx<long, std::wstring>( _1, 8 );
    wchar_t szNumber[20] = L"";
    swprintf_s(szNumber, 20, L"\\x%x", number);
    std::wstring retn(szNumber);
    return retn;
}

std::wstring Parser::_x2wchar_t(boost::match_results<std::wstring::const_iterator> match) const
{
    int x = 1;
    std::wstring _1 = match[1];
    long number = Utils::string2numberEx<long, std::wstring>( _1, 16 );
    std::wstring temp(L"");
    temp += (wchar_t)number;

    return temp;
}

std::wstring Parser::UTF8Normalize(std::wstring utf8String)
{
    std::wstring szOutputString(utf8String.c_str());
    try
    {
        /*
        * 处理\123 格式的八进制数据, 使其转为16进制
        */
        boost::wregex reg_re0(L"\\\\([0-7][0-7][0-7])", boost::regex::icase);
        boost::function<std::wstring (boost::match_results<std::wstring::const_iterator>)> function1 =
            boost::bind(&Parser::_oct2_x, this, _1);
        szOutputString = regex_replace(szOutputString, reg_re0, function1);

        /*
        * 处理\xEF\uEF格式转换为unicode字符串
        */
        boost::wregex reg_re2(L"(?:\\\\x|%|\\\\u)([0-9a-fA-F]{0,2})",boost::regex::icase);
        boost::function<std::wstring (boost::match_results<std::wstring::const_iterator>)> function2 =
            boost::bind(&Parser::_x2wchar_t, this, _1);
        szOutputString = regex_replace(szOutputString, reg_re2, function2);
    }
    catch (std::exception &e)
    {
        TRACE("%s\n", e.what());
        printf("%s\n", e.what());
        szOutputString = utf8String;
    }

    return szOutputString;
}

std::wstring Parser::UTF8Nor2Unicode(std::wstring utf8String, Utils::CodePage cp )
{
    std::wstring normalized = UTF8Normalize(utf8String);
    std::string utf8 = Utils::ASCIICopy<std::string>(normalized);
    std::wstring unicode = Utils::CodePage2Unicode(utf8, cp);

    return unicode;
}

std::wstring Parser::UTF8Nor2Unicode(std::string utf8String, Utils::CodePage cp )
{
    return UTF8Nor2Unicode(Utils::ASCIICopy<std::wstring>(utf8String), cp);
}

std::wstring Parser::UnicodeNormalize(std::wstring unicodeString)
{
    std::wstring szOutputString(unicodeString.c_str());
    try
    {
        /*
        * 处理\x963f, \u963f格式转换为unicode字符串
        */
        boost::wregex reg_re2(L"(?:\\\\x|%|\\\\u)([0-9a-fA-F]{0,4})",boost::regex::icase);
        boost::function<std::wstring (boost::match_results<std::wstring::const_iterator>)> function2 =
            boost::bind(&Parser::_x2wchar_t, this, _1);
        szOutputString = regex_replace(szOutputString, reg_re2, function2);
    }
    catch (std::exception &e)
    {
        TRACE("%s\n", e.what());
        printf("%s\n", e.what());
        szOutputString = unicodeString;
    }

    return szOutputString;
}

std::wstring Parser::UnicodeNor2Unicode(std::wstring unicodeString )
{
    std::wstring normalized = UnicodeNormalize(unicodeString);

    return normalized;
}
