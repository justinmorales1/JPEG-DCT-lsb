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
unsigned int tempEmbeddedMessageSize = 0;
unsigned int gBitCapacity;
unsigned int messageIndexValue;
unsigned int jpegImageTotalSize;
unsigned int coverMessageTotalSize;
unsigned int extractMessageSize = 0;
unsigned char *hexBuffer;
char *hexSizeBuffer;
unsigned char *gMsgBuffer;
unsigned char *gMsgBufferInBinary;
char sizeStr[16];
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
    

} TempCoverByte;

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


} ExtractedBits;

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

union
{
	struct MessageSize bitValue;
	unsigned char byteValue;


} TempMessageSizeBits;

//Note - Hiding text -i cover.jpg -h Message.txt > embeddingOutput.txt
//Note - Hiding jpg in a jpg -i cover2.jpg -h cover.jpg
//Note - Extracting text from a jpg -e -i cover2_hidden.jpg extractedText.txt > extractedOutput.txt
//Note - Extracting jpg from a jpg -e -i cover2_hidden.jpg extractedPic.jpg

// hide the data in a block of coefficients
void hideInBlock(JpegEncoderCoefficientBlock *data, JpegEncoderQuantizationTable &qt)
{
	unsigned int row, col;
	signed int number;

	if (gHideMsg == false) {
		return;
	}
    
	for(row = 0; row < JpegSampleWidth; row++)
		for(col = 0; col < JpegSampleWidth; col++)
		{
            jpegImageTotalSize++;
			qt.GetDataValue(row*JpegSampleWidth+col);   

			//Do not hide in coefficients that are 0 or a 1
            if ((*data)[row][col] == 0 || (*data)[row][col] == 1) {
                continue;
            } else if ((*data)[row][col] > 1) {
				//if coefficient is greater than 1, hide in it
                TempCoverByte.byteValue = (*data)[row][col];
                unsigned char messageBits = gMsgBufferInBinary[messageIndexValue];
                TempCoverByte.bitValue.bit0 = gMsgBufferInBinary[messageIndexValue];
                (*data)[row][col] = TempCoverByte.byteValue;
                messageIndexValue += 1;
            }
		}
	return;
} // END hideInBlock


// this function removes the bits from a block
void extractFromBlock(JpegDecoderCoefficientBlock data, const JpegDecoderQuantizationTable &qt)
{
	unsigned int row, col;
	signed int number;
	int dataCount = 0;

	if (gExtractMsg == false) {
		return;
	}

    for (row = 0; row < JpegSampleWidth; row++)
        for (col = 0; col < JpegSampleWidth; col++)
        {
            jpegImageTotalSize++;

			//don't extract from coefficients that are 1 or 0
            if ((data)[row][col] == 0 || (data)[row][col] == 1) {
                continue;
            }
            else if ((data)[row][col] > 1) {
                ExtractedBits.byteValue = (data)[row][col];
               //For the first 16 message bits we are extracting our 16 bit message size
               if (extractMessageSize != 16 && extractMessageSize < 16) {
                    gMsgBufferInBinary[extractMessageSize] = ExtractedBits.bitValue.bit0;
                    printf("%d", ExtractedBits.bitValue.bit0);
                    sizeStr[extractMessageSize] = ExtractedBits.bitValue.bit0;
                    extractMessageSize++;
               }
               else {
                   //This message buffer contains the rest of our binary values after size is extracted
                   gMsgBufferInBinary[messageIndexValue] = ExtractedBits.bitValue.bit0;       
               }
                //On the 16th bit, we now have our 2 size bytes
                if (extractMessageSize == 16) {
					//Combine our 2 size bytes to get the original message size
                    MessageSizeBits.bitValue.bit3 = sizeStr[0];
                    MessageSizeBits.bitValue.bit2 = sizeStr[1];
                    MessageSizeBits.bitValue.bit1 = sizeStr[2];
                    MessageSizeBits.bitValue.bit0 = sizeStr[3];
                    MessageSizeBits.bitValue.bit7 = sizeStr[4];
                    MessageSizeBits.bitValue.bit6 = sizeStr[5];
                    MessageSizeBits.bitValue.bit5 = sizeStr[6];
                    MessageSizeBits.bitValue.bit4 = sizeStr[7];
					TempMessageSizeBits.bitValue.bit3 = sizeStr[8];
					TempMessageSizeBits.bitValue.bit2 = sizeStr[9];
					TempMessageSizeBits.bitValue.bit1 = sizeStr[10];
					TempMessageSizeBits.bitValue.bit0 = sizeStr[11];
					TempMessageSizeBits.bitValue.bit7 = sizeStr[12];
					TempMessageSizeBits.bitValue.bit6 = sizeStr[13];
					TempMessageSizeBits.bitValue.bit5 = sizeStr[14];
					TempMessageSizeBits.bitValue.bit4 = sizeStr[15];
					tempEmbeddedMessageSize = TempMessageSizeBits.byteValue | MessageSizeBits.byteValue << 8;
					embeddedMessageSize = tempEmbeddedMessageSize;

                    embeddedMessageSize = embeddedMessageSize - 3;
					extractMessageSize++;
                }
                messageIndexValue++;
            }
        }
	return;
} // END extractFromBlock