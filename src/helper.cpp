// canalif.cpp
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright © 2000-2020 Ake Hedman, Grodans Paradis AB
// <info@grodansparadis.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#define _POSIX

#include "helper.h"

#include <algorithm>
#include <string>
#include <climits>

// https://stackoverflow.com/questions/105252/how-do-i-convert-between-big-endian-and-little-endian-values-in-c
template <typename T>
    T swap_endian(T u)
    {
        static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

        union
        {
            T u;
            unsigned char u8[sizeof(T)];
        } source, dest;

        source.u = u;

        for (size_t k = 0; k < sizeof(T); k++)
            dest.u8[k] = source.u8[sizeof(T) - k - 1];

        return dest.u;
    }

std::string
floathelper::hello()
{
    return "Hello World";
}

///////////////////////////////////////////////////////////////////////////////
// mem2double
//

double
floathelper::mem2double(uint8_t* buf)
{
    if ( nullptr == buf) {
        return 0;
    }

    return *((double *)buf);
}

///////////////////////////////////////////////////////////////////////////////
// double2mem
//

uint8_t *
floathelper::double2mem(double value, uint8_t* buf, size_t size)
{
    if ( nullptr == buf) {
        return NULL;
    }

    if ( size < 8 ) {
        return NULL;
    }

    uint8_t *p = (uint8_t *)&value;
    memcpy(buf,p,8);

    return buf;
}

///////////////////////////////////////////////////////////////////////////////
// mem2float
//

float
floathelper::mem2float(uint8_t* buf)
{
    if ( nullptr == buf) {
        return 0;
    }

    return *((float *)buf);
}

///////////////////////////////////////////////////////////////////////////////
// float2mem
//

uint8_t *
floathelper::float2mem(float value, uint8_t* buf, size_t size)
{
    if ( nullptr == buf) {
        return NULL;
    }

    if ( size < 4 ) {
        return NULL;
    }

    uint8_t *p = (uint8_t *)&value;
    memcpy(buf,p,4);

    return buf;
}

///////////////////////////////////////////////////////////////////////////////
// memint2double
//

double 
floathelper::memint2double(uint8_t *buf, size_t size, bool bSwap)
{
    bool bNegative = false;
    uint8_t wrkbuf[8];

    if ( nullptr == buf ) {
        return 0;
    }

    if ( (0 == size) || (size > 8) ) {
        return 0;
    }

    memset(wrkbuf, 0, sizeof(wrkbuf));

    // Check if sign bit is set
    if ( *buf & 0x80) {
        bNegative = true;
        memset(wrkbuf,0xff,sizeof(wrkbuf));
    }

    memcpy( wrkbuf /* + (8-size) */, buf, size);

    // if ( bNegative ) {
    //     if ( bSwap ) {
    //         wrkbuf[0] |= 0x80; // Set sign bit
    //     }
    //     else {
    //         wrkbuf[7] |= 0x80; // Set sign bit
    //     }
    // }

    int64_t val = *((int64_t *)wrkbuf);
    if ( bSwap ) {
        val = swap_endian<int64_t>(val);
    }

    return (double)val;
}

///////////////////////////////////////////////////////////////////////////////
// memuint2double
//

double 
floathelper::memuint2double(uint8_t *buf, size_t size, bool bSwap)
{
    uint8_t wrkbuf[8];

    if ( nullptr == buf ) {
        return 0;
    }

    if ( (0 == size) || (size > 8) ) {
        return 0;
    }

    memset(wrkbuf, 0, sizeof(wrkbuf));
    memcpy( wrkbuf, buf, size);

    uint64_t val = *((uint64_t *)wrkbuf);
    if ( bSwap ) {
        val = swap_endian<uint64_t>(val);
    }

    return (double)val;
}

///////////////////////////////////////////////////////////////////////////////
// convertMem2Double
//

Napi::Number
floathelper::convertMem2Double(const Napi::CallbackInfo& info)
{
    uint8_t buf[8];
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray() ) {
        Napi::TypeError::New(env, "Array expected")
          .ThrowAsJavaScriptException();
    }

    // Get buffer
    Napi::Array arr  = info[0].As<Napi::Array>();
   
    memset(buf,0,sizeof(buf));

    for ( unsigned int i=0; i<std::min((uint8_t)arr.Length(),(uint8_t)8); i++ ) {
        Napi::Value val = arr[i];
        if (val.IsNumber()) {
            buf[i] = (int)val.As<Napi::Number>();
        }
    }

    Napi::Number rv = Napi::Number::New(env, floathelper::mem2double(buf));

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// convertDouble2Mem
//

Napi::Array
floathelper::convertDouble2Mem(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber() ) {
        Napi::TypeError::New(env, "Number expected")
          .ThrowAsJavaScriptException();
    }

    Napi::Number value  = info[0].As<Napi::Number>();
   
    uint8_t buf[8];
    memset(buf,0,sizeof(buf));
    
    double dbl = value.DoubleValue();
    uint8_t *pp = floathelper::double2mem( dbl, buf, 8);
    if ( nullptr == pp ) {
        Napi::TypeError::New(env, "Conversion of double to memory failed")
          .ThrowAsJavaScriptException();
    }

    Napi::Array rv = Napi::Array::New(env,8);
    for ( int i=0; i<8; i++ ) {
        rv[uint8_t(i)] = Napi::Number::New(env,buf[i]);
    }
    
    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// convertMem2Single
//

Napi::Number
floathelper::convertMem2Single(const Napi::CallbackInfo& info)
{
    uint8_t buf[4];
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray() ) {
        Napi::TypeError::New(env, "Array expected")
          .ThrowAsJavaScriptException();
    }

    // Get buffer
    Napi::Array arr  = info[0].As<Napi::Array>();
   
    memset(buf,0,sizeof(buf));

    for ( unsigned int i=0; i<std::min((uint8_t)arr.Length(),(uint8_t)4); i++ ) {
        Napi::Value val = arr[i];
        if (val.IsNumber()) {
            buf[i] = (int)val.As<Napi::Number>();
        }
    }

    Napi::Number rv = 
        Napi::Number::New(env, floathelper::mem2float(buf));

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// convertSingle2Mem
//

Napi::Array
floathelper::convertSingle2Mem(const Napi::CallbackInfo& info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber() ) {
        Napi::TypeError::New(env, "Number expected")
          .ThrowAsJavaScriptException();
    }

    Napi::Number value  = info[0].As<Napi::Number>();
   
    uint8_t buf[4];
    memset(buf,0,sizeof(buf));
    
    if ( nullptr == floathelper::float2mem(value,buf,sizeof(buf)) ) {
        Napi::TypeError::New(env, "Conversion of float to memory failed")
          .ThrowAsJavaScriptException();
    }

    Napi::Array rv = Napi::Array::New(env,4);
    for ( int i=0; i<4; i++ ) {
        rv[uint8_t(i)] = Napi::Number::New(env,buf[i]);
    }
    
    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// convertMemUInt2Double
//

Napi::Number 
floathelper::convertMemUInt2Double(const Napi::CallbackInfo& info)
{
    bool bSwap = false;
    uint8_t buf[8];
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray() ) {
        Napi::TypeError::New(env, "One or two arguments expected. Array and bSwap")
          .ThrowAsJavaScriptException();
    }

    if ( 2 == info.Length() && !info[1].IsBoolean() ) {
        Napi::TypeError::New(env, "Second argument should be bSwap (boolean)")
          .ThrowAsJavaScriptException();
    }

    if ( 2 == info.Length() ) {
        Napi::Boolean b  = info[1].As<Napi::Boolean>();
        bSwap = b.ToBoolean();
    }

    // Get buffer
    Napi::Array arr  = info[0].As<Napi::Array>();
   
    memset(buf,0,sizeof(buf));

    uint8_t len = std::min((uint8_t)arr.Length(),(uint8_t)8);
    for ( unsigned int i=0; i<len; i++ ) {
        Napi::Value val = arr[i];
        if (val.IsNumber()) {
            buf[i] = (int)val.As<Napi::Number>();
        }
    }

    Napi::Number rv = Napi::Number::New(env, floathelper::memuint2double(buf,len,bSwap));

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// convertMemInt2Double
//

Napi::Number 
floathelper::convertMemInt2Double(const Napi::CallbackInfo& info)
{
    bool bSwap = false;
    uint8_t buf[8];
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsArray() ) {
        Napi::TypeError::New(env, "Two arguments expected. Array and size expected")
          .ThrowAsJavaScriptException();
    }

    if ( 2 == info.Length() && !info[1].IsBoolean() ) {
        Napi::TypeError::New(env, "Second argument should be bSwap (boolean)")
          .ThrowAsJavaScriptException();
    }

    if ( 2 == info.Length() ) {
        Napi::Boolean b  = info[1].As<Napi::Boolean>();
        bSwap = b.ToBoolean();
    }

    // Get buffer
    Napi::Array arr  = info[0].As<Napi::Array>();
   
    memset(buf,0,sizeof(buf));

    uint8_t len = std::min((uint8_t)arr.Length(),(uint8_t)8);
    for ( unsigned int i=0; i<len; i++ ) {
        Napi::Value val = arr[i];
        if (val.IsNumber()) {
            buf[i] = (int)val.As<Napi::Number>();
        }
    }

    Napi::Number rv = Napi::Number::New(env, floathelper::memint2double(buf,len,bSwap));

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// HelloWrapped
//

Napi::String
floathelper::HelloWrapped(const Napi::CallbackInfo& info)
{
    Napi::Env env            = info.Env();
    Napi::String returnValue = Napi::String::New(env, floathelper::hello());

    return returnValue;
}

///////////////////////////////////////////////////////////////////////////////
// Init
//

Napi::Object
floathelper::Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("hello", Napi::Function::New(env, floathelper::HelloWrapped));

    // http://svitlanamoiseyenko.com/2017/01/17/storing-of-floating-point-numbers-in-memory/
    exports.Set("convertMem2Double", Napi::Function::New(env, floathelper::convertMem2Double));
    exports.Set("convertDouble2Mem", Napi::Function::New(env, floathelper::convertDouble2Mem));
    
    exports.Set("convertMem2Single", Napi::Function::New(env, floathelper::convertMem2Single));
    exports.Set("convertSingle2Mem", Napi::Function::New(env, floathelper::convertSingle2Mem));
    
    exports.Set("convertMemUInt2Double", Napi::Function::New(env, floathelper::convertMemUInt2Double));
    exports.Set("convertMemInt2Double", Napi::Function::New(env, floathelper::convertMemInt2Double));


    return exports;
}