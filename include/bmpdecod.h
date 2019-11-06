#ifndef __BMPDECOD_H
#define __BMPDECOD_H
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
//  BMP Decoder Library.
//
//  Title:   BmpDecoder Class Implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class decodes Windows BMP file.
//
//

#include <iostream>

#include "bitimage.h"
#include "grexcept.h"
#include "bmp.h"

class BmpDecoder : public BitmapImageDecoder
{
public:
  BmpDecoder () ;
  virtual ~BmpDecoder () ;
  BmpDecoder (const BmpDecoder &) ;
  BmpDecoder &operator=(const BmpDecoder &) ;

  virtual void ReadImage (std::istream &, BitmapImage &) ;
private:
  void Initialize () ;
  void DoCopy (const BmpDecoder &) ;
  void CallProgressFunction (unsigned int percent) ;
} ;

#endif
