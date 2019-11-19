// Hide.cpp
// 
// This file contains all the routines to Embed/Extract Message Data
//

#include "include\Hide.h"

char tmpMessage[] = "Hello World! This is my message. Want it to be long to test the program.";

char gOutputFileName[260];
unsigned char gBitMask1[8] = { 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };
unsigned short gBitMask1_2[8] = { 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };
unsigned short gBitMask2_2[8] = { 0xFFFE, 0xFFFC, 0xFFF8, 0xFFF0, 0xFFE0, 0xFFC0, 0xFF80, 0xFF00 };
//unsigned char gBitMask3[8] = { 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
unsigned int embeddedMessageSize = 0;
unsigned int gBitCapacity;
unsigned int messageIndexValue;
unsigned int jpegImageTotalSize;
unsigned int coverMessageTotalSize;
unsigned int extractMessageSize;
char *hexBuffer;
char *gMsgBuffer;
char *gMsgBufferInBinary;
char str[8];
unsigned int gMsgSize;
double gAlpha = 1.0;			// jpenquan.h
double gUniformityFactor = 1.2;
unsigned int gImageQuality = 50;
bool gExtractMsg = false;
bool gDestroyMsg = false;
bool gWipeMsg = false;
bool gHideMsg = false;
double lg2; // lg2 = natural log 2
double lgQ; // lg2 of quality factor

// encoding/decoding objects
JpegEncoder gJpgEncoder;
JpegDecoder gJpgDecoder;
BmpEncoder gBitmapEncoder;
BmpDecoder gBitmapDecoder;
BitmapImage gImage;

// This function gets numBits from the message starting from the last position
// up until the end of the message (numBits range from 1 to 8)
unsigned char getBitsFromBuffer(unsigned int numBits, unsigned char *inBuffer, unsigned int inBufferLength)
{

	return(0);
} // getBitsFromBuffer

// this function gets the Uniformity Factor
double getUniformity_E(JpegEncoderCoefficientBlock data)
{
	int row, col;
	short tmpData;

	for(row = 0; row < JpegSampleWidth; row++)
		for(col = 0; col < JpegSampleWidth; col++)
			tmpData = data[row][col];

	return(0);
} // getUniformity_E


struct BITS
{
    unsigned char bit0 : 1; //This is the lsb for first byte.
    unsigned char bit1 : 1; 
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1; //This is the lsb for second byte byte.
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
};

union
{
    struct BITS bitValue;
    unsigned char byteValue;
    

} VAR;

struct ChangedBITS
{
    unsigned char bit0 : 1; //This is the lsb for first byte.
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char bit4 : 1; //This is the lsb for second byte byte.
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
};

union
{
    struct ChangedBITS bitValue;
    unsigned char byteValue;


} CBits;

struct MessageSize
{

    unsigned char bit4 : 1; //This is the lsb for second byte byte.
    unsigned char bit5 : 1;
    unsigned char bit6 : 1;
    unsigned char bit7 : 1;
    unsigned char bit0 : 1; //This is the lsb for first byte.
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
};

union
{
    struct MessageSize bitValue;
    unsigned char byteValue;


} MessageSizeBits;

//Note - Use these values for embedding when debugging -i cover.jpg -h data.txt > embeddingOutput.txt
//Note - Use these values for extraction when debugging -e -i cover_hidden.jpg > extractingOutput.txt

// hide the data in a block of coefficients
void hideInBlock(JpegEncoderCoefficientBlock *data, JpegEncoderQuantizationTable &qt)
{
	unsigned int row, col;
    signed int number;
	// check for simple conversions - no hiding/extracting
	if(gHideMsg == false) return;
    
	for(row = 0; row < JpegSampleWidth; row++)
		for(col = 0; col < JpegSampleWidth; col++)
		{
            jpegImageTotalSize++;

			qt.GetDataValue(row*JpegSampleWidth+col);   
            if ((*data)[row][col] == 0 || (*data)[row][col] == 1) {
                break;
            } else {
                //printf("The embedding JPEG coefficient value is : %d\n", (*data)[row][col]);
                VAR.byteValue = (*data)[row][col];
                unsigned char messageBits = gMsgBufferInBinary[messageIndexValue];
                //printf("The message Index value is %d \n", messageBits);
                //printf("The coefficient binary values are  %d%d%d%d %d%d%d%d \n", VAR.bitValue.bit7, VAR.bitValue.bit6, VAR.bitValue.bit5, VAR.bitValue.bit5
                //    , VAR.bitValue.bit3, VAR.bitValue.bit2, VAR.bitValue.bit1, VAR.bitValue.bit0);

                VAR.bitValue.bit0 = gMsgBufferInBinary[messageIndexValue];
                (*data)[row][col] = VAR.byteValue;

                //printf("The NEW JPEG coefficient value is : %d\n", (*data)[row][col]);
                //printf("The NEW JPEG coefficient binary values are  %d%d%d%d %d%d%d%d \n", VAR.bitValue.bit7, VAR.bitValue.bit6, VAR.bitValue.bit5, VAR.bitValue.bit5
                //    , VAR.bitValue.bit3, VAR.bitValue.bit2, VAR.bitValue.bit1, VAR.bitValue.bit0);
                         
                messageIndexValue += 1;
                //printf("The message index value is %d", messageIndexValue);
            }

		}

    
	return;
} // hideInBlock

// C++ program to convert hexadecimal to decimal 
#include<iostream> 
#include<string.h> 
using namespace std;



// takes the biffer, extracts a filename, and writes the rest of the data to disk
void writeMsg()
{
	return;
} // writeMsg

// uses the first 4 bytes in the message buffer to set the actual size of the message
void setMsgSize()
{
	return;
} // setMsgSize

// takes some number of bits and places them in a inBufferfer
int putBitsInBuffer(unsigned int numBits, unsigned char bits, unsigned char *outBuffer, unsigned int outBufferLength)
{
	return(SUCCESS);
} // putBitsInBuffer

// this function gets the Uniformity Factor
double getUniformity_D(JpegDecoderCoefficientBlock data)
{
	return(0);
} // getUniformity_D

// this function removes the bits from a block
void extractFromBlock(JpegDecoderCoefficientBlock data, const JpegDecoderQuantizationTable &qt)
{
    if (gExtractMsg == false) return;
    //unsigned char str[8];
    //gMsgBufferInBinary = (char *)malloc(4096);
    //memset(gMsgBufferInBinary, 0, size);
    unsigned int row, col;
    signed int number;
    int dataCount = 0;
    // check for simple conversions - no hiding/extracting   
    for (row = 0; row < JpegSampleWidth; row++)
        for (col = 0; col < JpegSampleWidth; col++)
        {
            jpegImageTotalSize++;

            if ((data)[row][col] == 0 || (data)[row][col] == 1) {
                break;
            }
            else {
                //printf("The JPEG extracted coefficient value is : %d\n", (data)[row][col]);
                CBits.byteValue = (data)[row][col];
                /*printf("The coefficient binary values are  %d%d%d%d %d%d%d%d \n", CBits.bitValue.bit7, CBits.bitValue.bit6, CBits.bitValue.bit5, CBits.bitValue.bit5
                    , CBits.bitValue.bit3, CBits.bitValue.bit2, CBits.bitValue.bit1, CBits.bitValue.bit0);*/

               //This if statement is adding the size of the embedded data into a buffer called str.
               if (extractMessageSize != 8) {
                    gMsgBufferInBinary[extractMessageSize] = CBits.bitValue.bit0;
                    str[extractMessageSize] = CBits.bitValue.bit0;
                    extractMessageSize++;
                    //continue;
               }
               else {
                   //This message buffer contains binary values
                   gMsgBufferInBinary[messageIndexValue] = CBits.bitValue.bit0;       
               }

                //The code below here is setting the byte value for the message size.
                if (extractMessageSize == 7) {
                    MessageSizeBits.bitValue.bit3 = str[0];
                    MessageSizeBits.bitValue.bit2 = str[1];
                    MessageSizeBits.bitValue.bit1 = str[2];
                    MessageSizeBits.bitValue.bit0 = str[3];
                    MessageSizeBits.bitValue.bit7 = str[4];
                    MessageSizeBits.bitValue.bit6 = str[5];
                    MessageSizeBits.bitValue.bit5 = str[6];
                    MessageSizeBits.bitValue.bit4 = str[7];
                    /*printf("The total message size binary values are  %d%d%d%d %d%d%d%d \n", MessageSizeBits.bitValue.bit7,
                        MessageSizeBits.bitValue.bit6, MessageSizeBits.bitValue.bit5, MessageSizeBits.bitValue.bit5
                        , MessageSizeBits.bitValue.bit3, MessageSizeBits.bitValue.bit2,
                        MessageSizeBits.bitValue.bit1, MessageSizeBits.bitValue.bit0);*/
                    printf("The FINAL hex value is %x \n", MessageSizeBits.byteValue);
                    embeddedMessageSize = MessageSizeBits.byteValue;
                    printf("The Hex value is %x \n", embeddedMessageSize);
                }

                messageIndexValue++;
            }
        }
	return;
} // extractFromBlock





 //bitfield read message



