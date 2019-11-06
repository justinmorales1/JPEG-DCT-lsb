#ifndef __BMBENCOD_H
#define __BMPENCOD_H

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
//  Title:  Windows Bitmap Encoder Class
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

#include <iostream>

#include "bitimage.h"
#include "bmp.h"

class BmpEncoder : public BitmapImageEncoder
{
public:
  BmpEncoder () ;
  BmpEncoder (const BmpEncoder &) ;
  virtual ~BmpEncoder () ;
  BmpEncoder &operator=(const BmpEncoder &) ;
  virtual void WriteImage (std::ostream &, BitmapImage &) ;
private:
  void Initialize () ;
  void DoCopy (const BmpEncoder &) ;
  void CallProgressFunction (unsigned int) ;
} ;

#endif
