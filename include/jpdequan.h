#ifndef __JPDEQUAN_H
#define __JPDEQUAN_H
//
//  Title:  JPEG Definitions and Utility Functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//


//
//  Title:  JPEG Decoder Quantization Table Class Implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class represents a quantization table used by the
//    JPEG decoder.
//


#include <iostream>
#include "jpeg.h"
#include "bitimage.h"

class JpegDecoder ;

class JpegDecoderQuantizationTable
{
public:
  JpegDecoderQuantizationTable() ;
  ~JpegDecoderQuantizationTable() {}

  // This function tells the caller if the quantization table has been
  // defined by the JPEG input stream.
  bool Defined () const ;

  // Function to read the quantization table from the input stream.
  void ReadTable (JpegDecoder &decoder, unsigned int precision) ;

  // This function builds the scaled quantization tables used in
  // fast IDCT implementations.
  void BuildScaledTables () ;

  // This function prints the contents of the quantization table to
  // an output stream.
  void Print (std::ostream &) const ;
  UBYTE2 GetDataValue (int index) const;

private:
  // Dummy Declarations for Required Member Functions
  JpegDecoderQuantizationTable (const JpegDecoderQuantizationTable&) ;
  JpegDecoderQuantizationTable &operator=(const JpegDecoderQuantizationTable&) ;

  // Quantization Values in Zig-Zag Order.
  UBYTE2 data_values [JpegSampleSize] ;


  // Scaling factor used for the scaled integer values.
  enum { QuantizationIntegerScale = 12, } ;

  // Scaled quantization values used for the fast IDCT implementations.
  double float_scaling [JpegSampleWidth][JpegSampleWidth] ;
  long integer_scaling [JpegSampleWidth][JpegSampleWidth] ;

  // This flag gets set to true when the quantization is defined in the
  // JPEG input stream. It is used to ensure that an compressed scan does
  // not attempt to use an undefined quantization table.
  bool table_defined ;

  friend class JpegDecoderDataUnit ;
} ;

inline bool JpegDecoderQuantizationTable::Defined () const
{
  return table_defined ;
}

inline std::ostream &operator<<(std::ostream &strm,
                                const JpegDecoderQuantizationTable &du)
{
  du.Print (strm) ;
  return strm ;
}

#endif
