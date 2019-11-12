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
unsigned int gBitCapacity = 0;

char *gMsgBuffer = NULL;
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


/*void readMsg(unsigned char bitValue1, unsigned char bitValue2, unsigned char bitValue3, unsigned char bitValue4, unsigned char bitValue5, unsigned char bitValue6, unsigned char bitValue7, unsigned char bitValue8)
{
    MESSAGE tMsg;
    //tMsg.BYTE.bit8 = 0xE7;
    tMsg.BYTE.bit1 = bitValue1; 
    tMsg.BYTE.bit2 = bitValue2;
    tMsg.BYTE.bit3 = bitValue3;
    tMsg.BYTE.bit4 = bitValue4;
    tMsg.BYTE.bit5 = bitValue5;
    tMsg.BYTE.bit6 = bitValue6;
    tMsg.BYTE.bit7 = bitValue7;
    tMsg.BYTE.bit8 = bitValue8;

    printf("1=%x, 2=%x, 3=%x, 4=%x, 5=%x, 6=%x, 7=%x, 8=%x \n",
        tMsg.BYTE.bit1, tMsg.BYTE.bit2, tMsg.BYTE.bit3, tMsg.BYTE.bit4,
        tMsg.BYTE.bit5, tMsg.BYTE.bit6, tMsg.BYTE.bit7, tMsg.BYTE.bit8);
    return;
}*/

// hide the data in a block of coefficients
void hideInBlock(JpegEncoderCoefficientBlock *data, JpegEncoderQuantizationTable &qt)
{
	unsigned int row, col;
    signed int number;
	// check for simple conversions - no hiding/extracting
	if(gHideMsg == false) return;
    VAR.byteValue = 0x4f;
    printf("The bit value 0 is %d \n", VAR.bitValue.bit0);
    printf("The bit value 1 is %d \n", VAR.bitValue.bit1);
    printf("The bit value 2 is %d \n", VAR.bitValue.bit2);
    printf("The bit value 3 is %d \n", VAR.bitValue.bit3);
    printf("The bit value 4 is %d \n", VAR.bitValue.bit4);
    printf("The bit value 5 is %d \n", VAR.bitValue.bit5);
    printf("The bit value 6 is %d \n", VAR.bitValue.bit6);
    printf("The bit value 7 is %d \n", VAR.bitValue.bit7);
    
    
    printf("The file size is %d\n", gMsgSize);
    printf("The message buffer values are %s\n", gMsgBuffer);

	for(row = 0; row < JpegSampleWidth; row++)
		for(col = 0; col < JpegSampleWidth; col++)
		{
          
			qt.GetDataValue(row*JpegSampleWidth+col);   
            if ((*data)[row][col] == 0 || (*data)[row][col] == 1) {
                printf("The values was a 0 or it was a 1\n");
                break;
            }
            else {         
                printf("The JPEG coefficient value is : %d\n", (*data)[row][col]);
                printf("The first hex value byte from the data.txt is %i and the literal value is %c", gMsgBuffer[col], gMsgBuffer[col]);
                char byte = gMsgBuffer[col];
                //byte = byte >> 4;
                
                //readMsg(0xE7);
                //(*data)[row][col] = 0xff;
                //printf("The new value is: %d\n", (*data)[row][col]);
            }
			//(*data)[row][col] &= 0;
			//(*data)[row][col] |= 0;	// hide data in coefficients

		}

    
	return;
} // hideInBlock

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

	return;
} // extractFromBlock





 //bitfield read message



