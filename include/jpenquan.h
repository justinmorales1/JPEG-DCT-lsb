#ifndef __JPENQUAN_H
#define __JPENQUAN_H
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
//  Title:  JpegEncoderQuantizationTable class definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class represents quantization table in the JPEG encoder.
//

#include "jpeg.h"

class JpegDecoder ;

class JpegEncoderQuantizationTable
{
public:
  JpegEncoderQuantizationTable() ;
  ~JpegEncoderQuantizationTable() {}


  UBYTE2 operator[](unsigned int index) const ;
  UBYTE2 &operator[](unsigned int index) ;

  void BuildScaledTables () ;
  UBYTE2 GetDataValue (int index);// jao

private:
  JpegEncoderQuantizationTable (const JpegEncoderQuantizationTable&) ;
  JpegEncoderQuantizationTable &operator=(const JpegEncoderQuantizationTable&) ;

  UBYTE2 data_values [JpegSampleSize] ;// jao here are the data values
  double float_scaling [JpegSampleWidth][JpegSampleWidth] ;

  friend class JpegEncoderDataUnit ;
} ;

// jao - I do not understand what the overloaded [] operator does???
inline UBYTE2 JpegEncoderQuantizationTable::operator[](unsigned int index) const
{
  return data_values [index] ;
}

inline UBYTE2 &JpegEncoderQuantizationTable::operator[](unsigned int index)
{
  return data_values [index] ;
}


#endif
