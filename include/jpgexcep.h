#ifndef __JPGEXCEP_H
#define __JPGEXCEP_H
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
//  Title:  JPEG Exception Definitions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

#include "grexcept.h"

// Base class for trappable JPEG errors.
class EJpegError : public EGraphicsException
{
public:
  EJpegError (const std::string &msg) : EGraphicsException (msg) {}
} ;

// Exception that makes reading the image impossible.
class EJpegFatal : public EGraphicsException
{
public:
  EJpegFatal (const std::string &msg) : EGraphicsException (msg) {}
} ;

// Exception thrown when the callback function returns a values
// indicating the caller wants to abort the decode.
class EJpegAbort : public EGraphicsException
{
public:
  EJpegAbort  () : EGraphicsException ("JPEG Aborted") {}
} ;

class EJpegValueOutOfRange : public EJpegError
{
public:
  EJpegValueOutOfRange () : EJpegError ("Value out of range") {}
} ;

class EJpegIndexOutOfRange : public EJpegError
{
public:
  EJpegIndexOutOfRange () : EJpegError ("Index out of range") {}
} ;

class EJpegBadOutputParameter : public EJpegError
{
public:
  EJpegBadOutputParameter (const std::string &msg) : EJpegError (msg) {}
} ;

class EJpegBadData : public EJpegError
{
public:
  EJpegBadData (const std::string &msg = "Bad input") : EJpegError (msg) {}
} ;

#endif

