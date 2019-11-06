#ifndef __GREXCEPT_H
#define __GREXCEPT_H
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
//  Title:  Graphics Exception Classes
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//

#include <stdexcept>

class EGraphicsException : public std::logic_error
{
public:
	EGraphicsException (std::string msg) : std::logic_error (msg.c_str ()) {}
} ;

class ESubscriptOutOfRange : public EGraphicsException
{
public:
  ESubscriptOutOfRange () : EGraphicsException ("Subscript out of range") {}
} ;

class EInvalidBitCount : public EGraphicsException
{
public:
  EInvalidBitCount () : EGraphicsException ("Invalid bit count") {}
} ;

class EGraphicsAbort : EGraphicsException
{
public:
  EGraphicsAbort () : EGraphicsException ("Abort") {}
} ;

#endif
