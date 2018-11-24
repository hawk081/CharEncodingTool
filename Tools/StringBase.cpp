#include "StdAfx.h"
#include "StringBase.h"

void StringBase::init( void )
{
    mData = L"";
    mType = ENC_UNICODE;
}

StringBase::StringBase(void)
{
    init();
}

StringBase::StringBase(std::wstring str)
{
    init();
    mData = str;
}

StringBase::StringBase(std::wstring str, EncodingType type )
{
    init();
    mType = type;
}

StringBase::StringBase(std::string str, EncodingType type )
{
    init();
    mType = type;
}

StringBase::~StringBase(void)
{
}

void StringBase::convertTo( EncodingType toType, std::wstring& dest )
{
}

void StringBase::convertTo( EncodingType toType, std::string& dest )
{
}

byte* StringBase::getBytes(EncodingType toType )
{
    byte* arr = new byte[5];
    return arr;
}
const wchar_t* StringBase::c_str()
{
    return mData.c_str();
}


