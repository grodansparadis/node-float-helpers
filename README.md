[![License](https://img.shields.io/badge/license-MIT-blue.svg)](http://choosealicense.com/licenses/mit/)
[![Travis Build Status](https://api.travis-ci.org/grodansparadis/node-red-contrib-vscp-tcp.svg?branch=master)](https://travis-ci.org/grodansparadis/node-red-contrib-vscp)

<img src="https://vscp.org/images/logo.png" width="100">

# node-float-helpers

Some helper functionality fort applications (binary protocol handling for example) that have floating point values or integers of various lengths stored in memory.

This is softwate that is part of the VSCP project. If you are new to VSCP you can find more info [here](https://www.vscp.org).


## Install
Install with

```bash
npm install node-float-helpers
```

optionally with '--save' to save dependency in the package.json file.

## Usage

Reference the module in the beginning of your file like this

```javascript
const vscp = require("node-float-helpers");
```

## convertMem2Double

Convert a double precision floating point value stored in an array (memory) to a javascript double.

**Example**

```javascript
const floatHelpers = require('bindings')('floathelpers');

// double 124.372 = 43 135 22 217 206 23 95 64
var arr1 = [43,135,22,217,206,23,95,64];
console.log('convertMem2Double should be 124.372 and is ',floatHelpers.convertMem2Double(arr1));
```
## convertDouble2Mem

Convert a double precision floating point value into an array of bytes (memory).

**Example**

```javascript
var dbl1 = 124.372;
var arr2 = floatHelpers.convertDouble2Mem(dbl1);
console.log('convertDouble2Mem 124.372 should be 43 135 22 217 206 23 95 64 ', arr2);
if ( JSON.stringify(arr2) === JSON.stringify(arr1) ) {
    console.log("Which is OK");
}
else {
    console.log("Which is an ERROR");
}
```

## convertMem2Single

Convert a single precision floating point value stored in an array (memory) to a javascript double.

**Example**

```javascript
// float 9.909819 = 158 142 30 65
var arr3 = [158,142,30,65];
console.log('\nconvertMem2Single should be 9.909819 and is ',
             floatHelpers.convertMem2Single(arr3));
```

---

This package is part of the [VSCP(Very Simple Control Protocol)](https://www.vscp.org) IoT framework.


## convertSingle2Mem

Convert a single precision floating point value into an array of bytes (memory).

**Example**

```javascript
var flt1 = 9.909819;
var arr4 = floatHelpers.convertSingle2Mem(flt1);
console.log('convertSingle2Mem 9.909819 should be 158 142 30 65 ', arr4);
if ( JSON.stringify(arr3) === JSON.stringify(arr4) ) {
    console.log("Which is OK");
}
else {
    console.log("Which is sm ERROR");
}
```

## convertMemUInt2Double

Convert an unsigned integer stored in memory (array) to a javascript double. 

Optionally the byte order can be swapped.

The integer can be 1/2/3/4/5/6/7/8 bytes which is 8/16/24/32/40/48/56/64 bits.

**Example**

```javascript
// convertMemUInt2Double
var arr_uint1 = [1];
console.log("convertMemUInt2Double 1-byte 1 = ", floatHelpers.convertMemUInt2Double(arr_uint1));
console.log("convertMemUInt2Double 1-byte 1 swap = ", floatHelpers.convertMemUInt2Double(arr_uint1,true));

var arr_uint2 = [1,2];
console.log("convertMemUInt2Double 2-byte 1,2 = ", floatHelpers.convertMemUInt2Double(arr_uint2));
console.log("convertMemUInt2Double 2-byte 1,2 swap = ", floatHelpers.convertMemUInt2Double(arr_uint2,true));

var arr_uint3 = [1,2,3];
console.log("convertMemUInt2Double 3-byte 1,2,3 = ", floatHelpers.convertMemUInt2Double(arr_uint3));
console.log("convertMemUInt2Double 3-byte 1,2,3 swap = ", floatHelpers.convertMemUInt2Double(arr_uint3,true));

var arr_uint4 = [1,2,3,4];
console.log("convertMemUInt2Double 4-byte 1,2,3,4 = ", floatHelpers.convertMemUInt2Double(arr_uint4));
console.log("convertMemUInt2Double 4-byte 1,2,3,4 swap = ", floatHelpers.convertMemUInt2Double(arr_uint4,true));

var arr_uint5 = [0,4,3,2,1];
console.log("convertMemUInt2Double 5-byte 0,4,3,2,1 = ", floatHelpers.convertMemUInt2Double(arr_uint5));
console.log("convertMemUInt2Double 5-byte 0,4,3,2,1 swap = ", floatHelpers.convertMemUInt2Double(arr_uint5,true));

var arr_uint6 = [0,0,0,3,2,1];
console.log("convertMemUInt2Double 6-byte 0,0,0,3,2,1 = ", floatHelpers.convertMemUInt2Double(arr_uint6));
console.log("convertMemUInt2Double 6-byte 0,0,0,3,2,1 swap = ", floatHelpers.convertMemUInt2Double(arr_uint6,true));

var arr_uint7 = [0,0,0,0,0,2,1];
console.log("convertMemUInt2Double 7-byte 0,0,0,0,0,2,1 = ", floatHelpers.convertMemUInt2Double(arr_uint7));
console.log("convertMemUInt2Double 7-byte 0,0,0,0,0,2,1 swap = ", floatHelpers.convertMemUInt2Double(arr_uint7,true));

var arr_uint8 = [0,0,0,0,0,0,0,1];
console.log("convertMemUInt2Double 8-byte 0,0,0,0,0,0,0,1 = ", floatHelpers.convertMemUInt2Double(arr_uint8));
console.log("convertMemUInt2Double 8-byte 0,0,0,0,0,0,0,1 swap = ", floatHelpers.convertMemUInt2Double(arr_uint8,true));
```

## convertMemInt2Double

Convert an signed integer stored in memory (array) to a javascript double. 

Optionally the byte order can be swapped.

The integer can be 1/2/3/4/5/6/7/8 bytes which is 8/16/24/32/40/48/56/64 bits.

**Example**

```javascript
// Signed integer

console.log("SIGNED INTEGERS");

var arr_int1a = [1];
console.log("convertMemInt2Double 1-byte 1 = ", floatHelpers.convertMemInt2Double(arr_int1a));
console.log("convertMemInt2Double 1-byte 1 swap = ", floatHelpers.convertMemInt2Double(arr_int1a,true));
var arr_int1b = [-8];
console.log("convertMemInt2Double 1-byte -8 = ", floatHelpers.convertMemInt2Double(arr_int1b));
console.log("convertMemInt2Double 1-byte -8 swap = ", floatHelpers.convertMemInt2Double(arr_int1b,true));

var arr_int2a = [1,0];
console.log("convertMemInt2Double 2-byte 1,0 = ", floatHelpers.convertMemInt2Double(arr_int2a));
console.log("convertMemInt2Double 2-byte 1,0 swap = ", floatHelpers.convertMemInt2Double(arr_int2a,true));
var arr_int2b = [0xff,0xff];
console.log("convertMemInt2Double 2-byte 0xff,0xff = ", floatHelpers.convertMemInt2Double(arr_int2b));
console.log("convertMemInt2Double 2-byte 0xff,0xff swap = ", floatHelpers.convertMemInt2
```

---
Copyright © 2000-2020 Åke Hedman, Grodans Paradis AB
