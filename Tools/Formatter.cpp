#include "StdAfx.h"
#include "Formatter.h"

Formatter::Formatter(void)
{
}

Formatter::~Formatter(void)
{
}

Formatter::Formatter(std::wstring unicodeString, FormatType fmt,  EncodingType enc)
{
    mOriginalString = unicodeString;
    mFormat = fmt;
    mEncoding = enc;
    Utils::CodePage cp = Utils::CP_UTF_8;
    switch(enc)
    {
    case ENC_UTF8:
    case ENC_GBK:
    case ENC_BIG5:
    case ENC_JPN:
    case ENC_KOR:
    case ENC_THAI:
        mTempString = Utils::ASCIICopy<std::wstring>(
            Utils::Unicode2CodePage(mOriginalString, getCodePageByENC(enc))
            );
        break;

    case ENC_UNICODE:
    default:
        mTempString = Utils::ASCIICopy<std::wstring>(unicodeString);
        break;
    }
    Format();
}

Formatter::Formatter(std::string unicodeString, FormatType fmt, EncodingType enc)
{
    mFormat = fmt;
    mEncoding = enc;
    mOriginalString = Utils::ASCIICopy<std::wstring>(unicodeString);
    mTempString = mOriginalString;
    Format();
}

Utils::CodePage Formatter::getCodePageByENC(EncodingType enc)
{
    Utils::CodePage cp = Utils::CP_DEFAULT;
    switch(enc)
    {
    case ENC_UTF8:
        cp = Utils::CP_UTF_8;
        break;
    case ENC_GBK:
        cp = Utils::CP_GBK;
        break;
    case ENC_BIG5:
        cp = Utils::CP_BIG5;
        break;
    case ENC_JPN:
        cp = Utils::CP_JPN;
        break;
    case ENC_KOR:
        cp = Utils::CP_KOR;
        break;
    case ENC_THAI:
        cp = Utils::CP_THAI;
        break;

    case ENC_UNICODE:
    default:
        break;
    }
    return cp;
}

std::wstring Formatter::Format()
{
    mFormattedString.clear();
    for(std::wstring::size_type i = 0; i < mTempString.size(); i++)
    {
        wchar_t szNumber[20] = L"";
        wchar_t current = mTempString.at(i);
        switch(mFormat)
        {
        case FMT_U:
            swprintf_s(szNumber, 20, L"\\u%X", current);
            break;
        case FMT_PERCENT:
            swprintf_s(szNumber, 20, L"%%%X", current);
            break;
        case FMT_OCT:
            swprintf_s(szNumber, 20, L"\\%o", current);
            break;

        case FMT_X:
        case FMT_ORI:
        default:
            swprintf_s(szNumber, 20, L"\\x%X", current);
            break;
        }
        mFormattedString += szNumber;
    }
    return mFormattedString;
}

