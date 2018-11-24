#pragma once
#include "stdafx.h"
#include "StringBase.h"
#include "Util.h"

class Parser
{
public:
    Parser(void);
    Parser(std::wstring OriginalString, EncodingType OriEType = ENC_UNICODE);
    Parser(std::string OriginalString, EncodingType OriEType = ENC_UNICODE);
    ~Parser(void);

private:
    EncodingType mEncodingType;
    FormatType mFormatType;
    std::wstring mOriginalString;
    std::wstring mParsedString;

private:
    std::wstring UTF8Nor2Unicode(std::wstring utf8String, Utils::CodePage cp = Utils::CP_UTF_8);
    std::wstring UTF8Nor2Unicode(std::string utf8String, Utils::CodePage cp = Utils::CP_UTF_8);
    std::wstring UTF8Normalize(std::wstring utf8String);
    std::wstring UnicodeNormalize(std::wstring unicodeString);
    std::wstring UnicodeNor2Unicode(std::wstring unicodeString );

private:
    std::wstring _oct2_x(boost::match_results<std::wstring::const_iterator> match) const;
    std::wstring _x2wchar_t(boost::match_results<std::wstring::const_iterator> match) const;

public:
    inline std::wstring getParsedString()
    {
        return mParsedString;
    }

    inline std::wstring getOriginalString()
    {
        return mOriginalString;
    }
};
