#pragma once
#include "stdafx.h"
#include "Utils/Utils.h"
#include "StringBase.h"

class Formatter
{
public:
    Formatter(void);
    Formatter(std::wstring unicodeString, FormatType fmt = FMT_ORI, EncodingType enc = ENC_UNICODE );
    Formatter(std::string unicodeString, FormatType fmt = FMT_ORI, EncodingType enc = ENC_UTF8 );
    ~Formatter(void);

public:
    std::wstring getFormattedWString()
    {
        return mFormattedString;
    }

    std::string getFormattedString()
    {
        return Utils::ASCIICopy<std::string>(mFormattedString);
    }
private:
    Utils::CodePage getCodePageByENC(EncodingType enc);
    std::wstring Format();
    std::wstring mOriginalString;
    std::wstring mFormattedString;
    std::wstring mTempString;
    FormatType mFormat;
    EncodingType mEncoding;
};
