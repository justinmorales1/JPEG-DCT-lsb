// Hide.h
//
// This file contains global variable externs
//

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "jpencobk.h"
#include "jpenquan.h"
#include "jpegenco.h"

#include "jpegdeco.h"
#include "jpdecomp.h"
#include "jpdequan.h"

#include "bmpdecod.h"
#include "bmpencod.h"
#include "bitimage.h"

// defines
#define SUCCESS 0
#define FAILURE 1
#define DONE 255

// Global Variables
extern char gOutputFileName[260];
extern char *gMsgBuffer;
extern unsigned int gMsgSize;
extern double gAlpha;
extern double gUniformityFactor;
extern unsigned int gImageQuality;
extern bool gExtractMsg;
extern bool gDestroyMsg;
extern bool gWipeMsg;
extern bool gHideMsg;
extern double lg2; // lg2 = natural log 2
extern double lgQ; // lg2 of quality factor
extern unsigned int gBitCapacity;

// encoding/decoding objects
extern JpegEncoder gJpgEncoder;
extern JpegDecoder gJpgDecoder;
extern BmpEncoder gBitmapEncoder;
extern BmpDecoder gBitmapDecoder;
extern BitmapImage gImage;

// function prototypes
int initializeHiding(char *MessageFileName);
void hideInBlock(JpegEncoderCoefficientBlock data, JpegEncoderQuantizationTable &qt);
void extractFromBlock(JpegDecoderCoefficientBlock data, const JpegDecoderQuantizationTable &qt);
void writeMsg();

// require initializing
unsigned char getBitsFromBuffer(unsigned int numBits, unsigned char *inBuffer, unsigned int inBufferLength);
int putBitsInBuffer(unsigned int numBits, unsigned char bits, unsigned char *outBuffer, unsigned int outBufferLength);

int readBitmap(char *inputFile);
int readJpg(char *inputFile, bool v);
int writeBitmap(char *outputFile);
int writeJpg(char *outputFile, bool g, bool p);

