"use strict";

//const floatHelpers = require('./build/Debug/floathelpers.node');
const floatHelpers = require('bindings')('floathelpers');

console.log('addon',floatHelpers);
console.log(floatHelpers.hello());

// double 124.372 = 43 135 22 217 206 23 95 64
var arr1 = [43,135,22,217,206,23,95,64];
console.log('convertMem2Double should be 124.372 and is ',floatHelpers.convertMem2Double(arr1));

var dbl1 = 124.372;
var arr2 = floatHelpers.convertDouble2Mem(dbl1);
console.log('convertDouble2Mem 124.372 should be 43 135 22 217 206 23 95 64 ', arr2);
if ( JSON.stringify(arr2) === JSON.stringify(arr1) ) {
    console.log("Which is OK");
}
else {
    console.log("Which is an ERROR");
}

// float 9.909819 = 158 142 30 65
var arr3 = [158,142,30,65];
console.log('\nconvertMem2Single should be 9.909819 and is ',
             floatHelpers.convertMem2Single(arr3));

var flt1 = 9.909819;
var arr4 = floatHelpers.convertSingle2Mem(flt1);
console.log('convertSingle2Mem 9.909819 should be 158 142 30 65 ', arr4);
if ( JSON.stringify(arr3) === JSON.stringify(arr4) ) {
    console.log("Which is OK");
}
else {
    console.log("Which is sm ERROR");
}


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
console.log("convertMemInt2Double 2-byte 0xff,0xff swap = ", floatHelpers.convertMemInt2Double(arr_int2b,true));