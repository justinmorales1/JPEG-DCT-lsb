#ifndef __JPENCOBK_H
#define __JPENCOBK_H
//
// Copyright (c) 1997,1998 Colosseum Builders, Inc.
// All rights reserved.
//
// Colosseum Builders, Inc. makes no warranty, expressed or implied
// with regards to this software. It is provided as is.
//
// See the README.TXT file that came with this software for restrictions
// on the use and redistribution of this file or send E-mail to
// info@colosseumbuilders.com
//

//
//  Title:  JpegEncoderCoefficientBlock class definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class is used to store DCT coefficients within component object.
//

#include "jpeg.h"

class JpegEncoderCoefficientBlock
{
public:
  BYTE2 *operator[](unsigned int index) ;
  BYTE2 &ZigZagInput (unsigned int index) ;
private:
  BYTE2 data [JpegSampleWidth][JpegSampleWidth] ;
} ;

inline BYTE2 *JpegEncoderCoefficientBlock::operator[](unsigned int index)
{
  return data [index] ;
}

inline BYTE2 &JpegEncoderCoefficientBlock::ZigZagInput (unsigned int index)
{
  return ((BYTE2 *) data) [JpegZigZagInputOrder (index)] ;
}

#endif
