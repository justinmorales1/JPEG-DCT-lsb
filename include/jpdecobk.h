#ifndef __DECOEFBK_H
#define __DECOEFBK_H
//
//  Title:  JPEG Definitions and Utility Functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//


//
//  Title: JPEG Decoder Coefficient Block Definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This type is used to hold DCT coefficients for a data unit.
//

#include "jpeg.h"

typedef BYTE2 JpegDecoderCoefficientBlock [JpegSampleWidth][JpegSampleWidth] ;

#endif
