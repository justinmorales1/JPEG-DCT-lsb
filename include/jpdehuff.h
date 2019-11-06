#ifndef __JPDEHUFF_H
#define __JPDEHUFF_H
//
//  Title:  JPEG Definitions and Utility Functions
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//


//
//  Title:  JPEG Decoder Huffman Table Class Implementation
//
//  Author:  John M. Miano  miano@colosseumbuilders.com
//
//  Description:
//
//    This class represents a Huffman Table used by the JpegDecoder
//    class.
//


#include "jpeg.h"
#include "bitimage.h"

class JpegDecoder ;

class JpegHuffmanDecoder
{
public:
  JpegHuffmanDecoder () ;
  virtual ~JpegHuffmanDecoder () {}

  // DECODING FUNCTIONS

  // Returns true if the table has been defined...in other words,
  // if ReadTable () has completed successfully. This function is
  // called before the table is used to decode a scan to ensure
  // the the image does not reference a Huffman Table that has
  // not been defined.
  bool Defined () const ;

  // This function reads a Huffman table from the input stream.
  unsigned int ReadTable (JpegDecoder &) ;

  // Function to decode the next value in the input stream.
  int Decode (JpegDecoder &) ;

  // This is a debugging function that writes the Huffman table
  // to a streamt.
  void Dump (std::ostream &strm) const ;

private:
  JpegHuffmanDecoder (const JpegHuffmanDecoder &) ;
  JpegHuffmanDecoder &operator=(const JpegHuffmanDecoder &) ;

  // This function builds the structures needed for Huffman
  // decoding after the table data has been read.
  void MakeTable (UBYTE1 huffbits [JpegMaxHuffmanCodeLength]) ;

  // Maximum Huffman code value of length N
  int maxcode [JpegMaxHuffmanCodeLength] ;
  // Minimum Huffman code value of length N
  int mincode [JpegMaxHuffmanCodeLength] ;
  // Index into "values" for minimum code of length N
  UBYTE1 valptr [JpegMaxHuffmanCodeLength] ;
  // Huffman values
  UBYTE1 huff_values [JpegMaxNumberOfHuffmanCodes] ;

  bool table_defined ;
} ;

#endif
