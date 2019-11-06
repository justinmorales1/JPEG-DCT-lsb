#ifndef __BMP_H
#define __BMP_H
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
// BMP Library.
//
//  Title:   Windows Bitmap Definitions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

#include "grexcept.h"

class EBmpFileReadError : public EGraphicsException
{
public:
  EBmpFileReadError () : EGraphicsException ("Error reading BMP input file") {}
  EBmpFileReadError (const EBmpFileReadError &be) : EGraphicsException (be) {}
  EBmpFileReadError &operator=(const EBmpFileReadError &ge)
  {
    this->EGraphicsException::operator=(ge) ;
    return *this ;
  }
} ;

class EBmpNotABmpFile : public EGraphicsException
{
public:
  EBmpNotABmpFile () : EGraphicsException ("Not a Windows Bitmap stream") {}
  EBmpNotABmpFile (const EBmpNotABmpFile &be) : EGraphicsException (be) {}
  EBmpNotABmpFile &operator=(const EBmpNotABmpFile &ge)
  {
    this->EGraphicsException::operator=(ge) ;
    return *this ;
  }
} ;

class EBmpCorruptFile : public EGraphicsException
{
public:
  EBmpCorruptFile () : EGraphicsException ("Corrupt Windows Bitmap stream") {}
  EBmpCorruptFile (const EBmpCorruptFile &be) : EGraphicsException (be) {}
  EBmpCorruptFile &operator=(const EBmpCorruptFile &ge)
  {
    this->EGraphicsException::operator=(ge) ;
    return *this ;
  }
} ;

class EBmpNotSupported : public EGraphicsException
{
public:
  EBmpNotSupported () : EGraphicsException ("Unsupported Bitmap Format") {}
  EBmpNotSupported (const EBmpNotSupported &be) : EGraphicsException (be) {}
  EBmpNotSupported &operator=(const EBmpNotSupported &ge)
  {
    this->EGraphicsException::operator=(ge) ;
    return *this ;
  }
} ;

#endif
