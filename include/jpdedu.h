#ifndef __JPDEDU_H
#define __JPDEDU_H
//
//  Title:  JPEG Definitions and Utility Functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//


//
//  Decoder Data Unit Class Definition
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Descrition:
//
//    The DataUnit class represents an 8x8 sample block for one
//    component of the JPEG image.
//
//

#include <iostream>

#include "jpeg.h"
#include "jpdequan.h"
#include "jpdecobk.h"

class JpegDecoderDataUnit ;

std::ostream &operator<<(std::ostream &, JpegDecoderDataUnit &) ;

class JpegDecoderDataUnit
{
public:
  // Declaration of a type for pointers to member functions
  // for implementing the IDCT. The input parameters are
  // The IDCT coefficients and the [de]quantization table.
  typedef JpegDecoderDataUnit &(JpegDecoderDataUnit::*IDctFunction) (
                                JpegDecoderCoefficientBlock,
                                const JpegDecoderQuantizationTable  &) ;

  JpegDecoderDataUnit() {}
  virtual ~JpegDecoderDataUnit () {}

  // Utility function to write the IDCT values to an output stream.
  void Print (std::ostream &) const ;

  // General IDCT Function
  JpegDecoderDataUnit &InverseDCT (
                        JpegDecoderCoefficientBlock cb,
                        const JpegDecoderQuantizationTable  &qt) ;

  // These are the IDCT implementations.
  JpegDecoderDataUnit &FloatInverseDCT (JpegDecoderCoefficientBlock,
                             JpegDecoderQuantizationTable  &) ;
  JpegDecoderDataUnit &IntegerInverseDCT (JpegDecoderCoefficientBlock,
                               const JpegDecoderQuantizationTable  &) ;

  // Operators to retrieve the individual IDCT values.
  JPEGSAMPLE *operator [] (unsigned int ii) ;
  JPEGSAMPLE const* operator [] (unsigned int ii) const ;

private:
  // Dummy Declarations For Required Members Functions 
  JpegDecoderDataUnit (const JpegDecoderDataUnit &) ;
  JpegDecoderDataUnit &operator=(const JpegDecoderDataUnit &) ;

  // The IDCT values.
  UBYTE1 values [JpegSampleWidth][JpegSampleWidth] ;

  // This is a pointer to the member function that implements
  // the desired IDCT function.
  static IDctFunction idct_function ;
} ;

inline JPEGSAMPLE *JpegDecoderDataUnit::operator [] (unsigned int ii)
{
 return values [ii] ;
}

inline JPEGSAMPLE const* JpegDecoderDataUnit::operator [] (unsigned int ii) const
{
  return values [ii] ;
}

inline std::ostream &operator<<(std::ostream &strm, const JpegDecoderDataUnit &du)
{
  du.Print (strm) ;
  return strm ;
}

inline JpegDecoderDataUnit &JpegDecoderDataUnit::InverseDCT (
                        JpegDecoderCoefficientBlock cb,
                        const JpegDecoderQuantizationTable  &qt)
{
  return (this->*idct_function) (cb, qt) ;
}


#endif
