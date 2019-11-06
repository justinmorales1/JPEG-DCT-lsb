#ifndef __JPEG_H
#define __JPEG_H
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
//  Title:  JPEG Definitions and Utility Functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

#include "datatype.h"
#include "jpmarker.h"

// Table B.5
const int JpegMaxHuffmanTables = 4 ;
// Table B.4
const int MaxQuantizationTables = 4 ;

// Table B.2
const int JpegMaxComponentsPerFrame = 255 ;
// Table B.3
const int JpegMaxComponentsPerScan = 4 ;

// Table B.2
const int JpegMinSamplingFrequency = 1 ;
const int JpegMaxSamplingFrequency = 4 ;


// A.1.3
const int JpegSampleWidth = 8 ;
const int JpegSampleSize = JpegSampleWidth * JpegSampleWidth ;

// Functions to convert to Zig-Zag order
unsigned int JpegZigZagInputOrder (unsigned int item) ;
unsigned int JpegZigZagOutputOrder (unsigned int item) ;

// Datatype used to represent a sample value.
typedef UBYTE1 JPEGSAMPLE ; // For 12-Bits this would be UBYTE2
typedef BYTE1 JPEGCOEFFICIENT ;

const int JpegMinSampleValue = 0 ;
const int JpegMaxSampleValue = 255 ; // For 12-Bits this would be 4095
const int JpegMidpointSampleValue = 128 ; // For 12-Bits this 2048


// Table B.5
const unsigned int JpegMaxHuffmanCodeLength = 16 ;
const unsigned int JpegMaxNumberOfHuffmanCodes = 256 ;

// B.2.3
const int JpegMaxDataUnitsPerMCU = 10 ;

// Section B.2.3 Table B.3
const int JpegMaxSuccessiveApproximation = 13 ;

// Section B.2.4.1 Table B.4

const int JpegMax8BitQuantizationValue = 255 ;
const int JpegMinQuantizationValue = 1 ;

extern const unsigned int JpegZigZagInputOrderCodes [JpegSampleSize] ;
extern const unsigned int JpegZigZagOutputOrderCodes [JpegSampleSize] ;

inline unsigned int JpegZigZagInputOrder (unsigned int item)
{
  return JpegZigZagInputOrderCodes [item] ;
}

inline unsigned int JpegZigZagOutputOrder (unsigned int item)
{
  return JpegZigZagOutputOrderCodes [item] ;
}


#endif
