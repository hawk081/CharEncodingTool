#pragma once

#include <string>

using namespace std;

typedef unsigned char byte;

enum EncodingType {
    ENC_UNICODE,
    ENC_UTF8,
    ENC_GBK,
    ENC_BIG5,
    ENC_JPN,
    ENC_KOR,
    ENC_THAI,

    ENC_COUNT
};

enum FormatType {
    FMT_ORI,
    FMT_X,
    FMT_U,
    FMT_PERCENT,
    FMT_OCT,

    FMT_COUNT
};

class StringBase
{
public:
    StringBase(void);
    StringBase(std::wstring str);
    StringBase(std::wstring str, EncodingType type );
    StringBase(std::string str, EncodingType type );
    ~StringBase(void);

protected:
    std::wstring mData;
    EncodingType mType;
    void init( void );
public:
    void convertTo( EncodingType toType, std::wstring& dest );
    void convertTo( EncodingType toType, std::string& dest );
    byte*    getBytes(EncodingType toType );
    const wchar_t* c_str();
};
