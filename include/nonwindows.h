#ifndef __WINDOWS_H
#define __WINDOWS_H
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

#include "datatype.h"

enum { BI_RGB=0, BI_RLE8=1, BI_RLE4=2, BI_BITFIELDS=3 } ;
 
#pragma pack (1)
#pragma option -a1
struct RGBQUAD
{
  UBYTE1 rgbBlue ;
  UBYTE1 rgbGreen ;
  UBYTE1 rgbRed ;
  UBYTE1 rgbReserved ;
} ;
#pragma option -a.

#pragma pack (1)
#pragma option -a1
struct RGBTRIPLE
{
  UBYTE1 rgbtBlue ;
  UBYTE1 rgbtGreen ;
  UBYTE1 rgbtRed ;
} ;
#pragma option -a.

#pragma pack (1)
#pragma option -a1
struct BITMAPCOREHEADER
{
  UBYTE4 bcSize ;
  UBYTE2 bcWidth ;
  UBYTE2 bcHeight ;
  UBYTE2 bcPlanes ;
  UBYTE2 bcBitCount ;
} ;
#pragma option -a.

#pragma pack (1)
#pragma option -a1
struct BITMAPINFOHEADER
{
  UBYTE4 biSize ;
  BYTE4 biWidth ;
  BYTE4 biHeight ;
  BYTE2 biPlanes ;
  BYTE2 biBitCount ;
  UBYTE4 biCompression ;
  UBYTE4 biSizeImage ;
  BYTE4 biXPelsPerMeter ;
  BYTE4 biYPelsPerMeter ;
  UBYTE4 biClrUsed ;
  UBYTE4 biClrImportant ;
} ;
#pragma option -a.

#pragma pack (1)
#pragma option -a1
struct BITMAPFILEHEADER
{
  BYTE2 bfType ;
  UBYTE4 bfSize ;
  BYTE2 bfReserved1 ;
  BYTE2 bfReserved2 ;
  UBYTE4 bfOffBits ;
} ;
#pragma option -a.

#endif
