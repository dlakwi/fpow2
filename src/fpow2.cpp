// fpow2.cpp
// 2020-12-31

// from util-C.h in the ETE Toolkit
// https://github.com/etetoolkit/ext_apps/blob/master/src/clustal-omega-1.2.1/src/hhalign/util-C.h
// https://github.com/etetoolkit/ext_apps

/*********************************************************************
 * Clustal Omega - Multiple sequence alignment
 *
 * Copyright (C) 2010 University College Dublin
 *
 * Clustal-Omega is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This file is part of Clustal-Omega.
 *
 ********************************************************************/

#include <Arduino.h>

// modified for Arduino for AVR microcontrollers
// float : 32 bits - IEEE-754 s8.23 - 1 sign bit, 8 exponent bits, 23 fraction bits
// int   : 32 bit int32_t

// float
// sign     ~ 0x80000000  1000 0000 0000 0000 0000 0000 0000 0000
// exponent ~ 0x7F800000  0111 1111 1000 0000 0000 0000 0000 0000
// fraction ~ 0x007FFFFF  0000 0000 0111 1111 1111 1111 1111 1111
// 3 << 22  ~ 0x00C00000  0000 0000 1100 0000 0000 0000 0000 0000 == 
//          ~ 0x4B400000  0100 1011 0100 0000 0000 0000 0000 0000 == 1.5e150 == 12582912.0 == 12582912

float large_integer = 0x00C00000;  // 3 << 22

/////////////////////////////////////////////////////////////////////////////////////
// fast 2^x
// ATTENTION: need to compile with g++ -fno-strict-aliasing when using -O2 or -O3!!!
// Relative deviation < 1.5E-4
/////////////////////////////////////////////////////////////////////////////////////

float fpow2( float x )
{
  if ( x >=  128.0 ) return __FLT_MAX__;
  if ( x <= -128.0 ) return __FLT_MIN__;

  int32_t* px = (int32_t*)( &x );                 // store address of float as pointer to long
  float    tx = ( x - 0.5f ) + large_integer;     // temporary value for truncation: x-0.5 is added to a large integer (3<<22)

  int32_t  lx = *( (int32_t*)&tx ) - 0x4b400000;  // integer value of x
  float    dx = x - (float)( lx );                // float remainder of x

  // cubic apporoximation of 2^x for x in the range [0, 1]
  x = 1.0f + dx * ( 0.6960656421638072f
                    + dx * ( 0.224494337302845f
                             + dx * ( 0.07944023841053369f ) ) );
  *px += ( lx << 23 );                            // add integer power of 2 to exponent

  return x;
}
