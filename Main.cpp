// Main.cpp
//
// This routine is used solely to pass arguments to either the encoder or decoder.
// It checks the input file type and makes a decision based on the extension
// if the extension is ".bmp" then call the encoder
// if the extension is ".jpg" then call the decoder

#include <iostream>
#include <fstream>
#include <string.h>
#include <io.h>
#include "include\Hide.h"

using namespace std ;

struct DataBits
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
    struct DataBits bitValue;
    unsigned char byteValue;
    int count = 0;


} DataVAR;

void Usage (int argc, char *argv [])
{
  char *file ;

  file = argv [0] ;

  cerr << endl;
  cerr << "Encoder Usage: " << file << " [-flags] bmp-file jpg-file " << endl ;
  cerr << "Flags:  -g				Grayscale Output (to jpg only)" << endl ;
  cerr << "        -p				Progressive Output (to jpg only)" << endl ;
  cerr << "        -v				Verbose Output (to bitmap only)" << endl ;

  cerr << "        -i input file	cover file (jpg or bmp)" << endl ;
  cerr << "        -o output file	stego file (if extracting message, no output file)" << endl ;
  cerr << "        -h message file	hide a message" << endl ;
  cerr << "        -e				extract a message" << endl ;
  cerr << "        -w				wipe a message (will wipe bits in output file)" << endl ;	// wipe a message (replaces message with zeros)
  cerr << "        -d				destroy a message (will replace bits in output file)" << endl ;// destroy a message (replaces message with pseudornd bits)
  cerr << "        -u [1.0 to 99.9 def:1.2]	uniformity adjustment (1.2" << endl ;
  cerr << "        -a [0.01 - 9.99 def:1] alpha factor" << endl ;
  cerr << "        -q [10 - 100 def:50]	quality factor" << endl ;

  exit (1) ;
} // Usage

int main(int argc, char *argv[])
{
	int test = 0, i, x, fileno, size;
    int dataCount = 0;
	char ch, *ext, *inputFile, *outputFile, inExt, outExt;
	bool g, p, v;
	double tmpDbl;
	unsigned int tmpInt;
	FILE *fptr;

	if(argc < 2) Usage(argc, argv);

	// initialize variables
	inputFile = NULL;
	outputFile = NULL;
	g = false;
	p = false;
	v = false;
	lg2 = log( (double) 2); // lg2 = natural log 2
	srand(1);
	gBitCapacity = 0;

	for(i = 1; i < argc; i++)
	{
		if(*argv[i] == '-')
		{
			ch = *(argv[i]+1);
			switch(ch)
			{
			case 'g':	// greyscale
				g = true;
				break;

			case 'p':	// progressive
				p = true;
				break;

			case 'v':	// verbose output
				v = true;
				break;

			case 'a':	// alpha adjustment factor (0.01 - 9.99)
				i++;
				tmpDbl = atof(argv[i]);
				if(tmpDbl < 0.1 || tmpDbl > 9.99) tmpDbl = 1.0;
				gAlpha = tmpDbl;
				break;

			case 'q':	// Image quality factor (10-100)
				i++;
				tmpInt = atoi(argv[i]);

				if(tmpInt < 10) gImageQuality  = 10;

				else if(tmpInt > 100) gImageQuality = 100;

				else gImageQuality = tmpInt;

				break;

			case 'e':	// extract a message
				gExtractMsg = true;
				break;

			case 'w':	// wipe a message (replaces message with zeros)
				gWipeMsg = true;
				break;

			case 'd':	// destroy a message (replaces message with pseudornd bits)
				gDestroyMsg = true;
				break;

			case 'h':	// hide - provide message file name
				i++;
                char buffer[4096];
				fptr = fopen(argv[i], "rb");
               
				if(fptr == NULL)
				{
					printf("Could not open message file %s\n\n", argv[i]);
					exit(1);
				}

				fileno = _fileno(fptr);
				size = (int) _filelength(fileno) + (int) strlen(argv[i]) + 5; // get length of message file
															// the +5 allows for 4-byte length & NULL terminator
				gMsgBuffer = (char *) malloc(size);
                gMsgBufferInBinary = (char *)malloc(4096);
				if(gMsgBuffer == NULL)
				{
					printf("Could not allocate memory for message file.\n\n");
					exit(1);
				}           
				memset(gMsgBuffer, 0, size);
                memset(gMsgBufferInBinary, 0, size);
				gMsgSize = 0;
				*(gMsgBuffer + gMsgSize++) = size >> 24;
				*(gMsgBuffer + gMsgSize++) = (size >> 16) & 0xFF;
				*(gMsgBuffer + gMsgSize++) = (size >> 8) & 0xFF;
				*(gMsgBuffer + gMsgSize++) = size & 0xFF;
				//strcpy( (gMsgBuffer+4) , argv[i]); // copy the filename as part of the message
				//gMsgSize += (int) strlen(&gMsgBuffer[4]) + 1; // 1 for NULL
                gMsgSize += (unsigned int)fread(gMsgBuffer, 1, size, fptr);	// read entire message file into memory
                //gMsgSize += (unsigned int)fread(&gMsgBuffer[gMsgSize], 1, size, fptr);	// read entire message file into memory
				//gMsgSize += (unsigned int) fread(buffer, 1, size, fptr);	// read entire message file into memory
                //printf("The message buffer values for the file name is %s\n", gMsgBuffer[4]);
                printf("The message buffer values are %s\n", gMsgBuffer);
                printf("The message size is %d\n", gMsgSize);

                for (int i = 0; i < gMsgSize; i++) {
                    unsigned char byte = gMsgBuffer[i];//gMsgBufferInBinary
                    printf("The first hex value byte from the data.txt is %x and the literal value is %c \n", gMsgBuffer[i], gMsgBuffer[i]);
                    DataVAR.byteValue = byte;

                    printf("The bit value 0 is %d \n", DataVAR.bitValue.bit0);
                    printf("The bit value 1 is %d \n", DataVAR.bitValue.bit1);
                    printf("The bit value 2 is %d \n", DataVAR.bitValue.bit2);
                    printf("The bit value 3 is %d \n", DataVAR.bitValue.bit3);
                    printf("The bit value 4 is %d \n", DataVAR.bitValue.bit4);
                    printf("The bit value 5 is %d \n", DataVAR.bitValue.bit5);
                    printf("The bit value 6 is %d \n", DataVAR.bitValue.bit6);
                    printf("The bit value 7 is %d \n", DataVAR.bitValue.bit7);
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit7;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit6;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit5;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit4;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit3;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit2;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit1;
                    gMsgBufferInBinary[dataCount++] = DataVAR.bitValue.bit0;


                }
                for (int i = 0; i < dataCount; i++) {
                    printf("%d", gMsgBufferInBinary[i]);
                }
				fclose(fptr);
				gHideMsg = true;
				getBitsFromBuffer(0, NULL, 0);	// reset buffer static variables
				break;

			case 'i':	// input file name
				i++;
				inputFile = argv[i];
				break;

			case 'u':	// setting the uniformity factor
				tmpDbl = atof(argv[i+1]);
				if(tmpDbl < 1.0 || tmpDbl > 99.99) tmpDbl = 1.2; // choose default value
				gUniformityFactor = tmpDbl;
				break;

			case 'o':	// output file name
				i++;
				outputFile = argv[i];
				break;

			} // switch
		} // argv == '-'
	} // for loop through arguments

	// MUST have an input file
	if(inputFile == NULL)
	{
		cerr << "MUST have an input file.\n" << endl;
		Usage(argc, argv);
	}

	x = (int) strlen(inputFile);
	ext = inputFile + x - 4; // get extension of file name
	if(strcmp(ext, ".bmp") == 0) inExt = 'b';
	else if(strcmp(ext, ".jpg") == 0) inExt = 'j';
	else
	{
		cerr << "Must use '.bmp' or '.jpg' as input files." << endl;
		Usage(argc, argv);
	}

	// DETERMINE THE OPERATION
	// Converting
	if(gHideMsg == false && gExtractMsg == false && gWipeMsg == false && gDestroyMsg == false)
	{
		// if no output file name, get it from input file
		if(outputFile == NULL)
		{
			outputFile = gOutputFileName;
			strcpy(gOutputFileName, inputFile);
			// lop off extension
			gOutputFileName[x-4] = 0;
			if(inExt == 'j')
			{
				outExt = 'b';
				strcat(gOutputFileName, ".bmp");
			}
			else
			{
				outExt = 'j';
				strcat(gOutputFileName, ".jpg");
			}
		}
		else
		{
			x = (int) strlen(outputFile);
			ext = outputFile + x - 4; // get extension of file name
			if(strcmp(ext, ".bmp") == 0) outExt = 'b';
			else if(strcmp(ext, ".jpg") == 0) outExt = 'j';
			else
			{
				cerr << "Must use '.bmp' or '.jpg' as output files." << endl;
				Usage(argc, argv);
			}
		}

		if(inExt == outExt)	// nothing to be done
			cerr << "You are converting a file to the same type - this will produce a copy." << endl;

        // TODO: check for in/out files having the same name
		if(inExt == 'j')
			readJpg(inputFile, v);
		else
			readBitmap(inputFile);

		if(outExt == 'j')
			writeJpg(outputFile, g, p);
		else
			writeBitmap(outputFile);

		return(SUCCESS);
	}

	// Hiding
	if(gHideMsg)
	{
		if(gExtractMsg || gWipeMsg || gDestroyMsg)
		{
			cerr << "Can't hide and also extract, wipe, or destroy a message." << endl;
			Usage(argc, argv);
		}

		// treat DC coefficeint a bit differently
		// this calculates lg2 of quality factor less hiding in DC coeffcients
		lgQ = log( (double) gImageQuality)/lg2; // lgQ==1 will nullify effect
		lgQ = 2/lgQ;

		// if no output file name, get it from input file
		if(outputFile == NULL)
		{
			outputFile = gOutputFileName;
			strcpy(gOutputFileName, inputFile);
			// lop off extension
			gOutputFileName[x-4] = 0;
			strcat(gOutputFileName, "_hidden.jpg");
			outExt = 'j';
		}
		else
		{
			x = (int) strlen(outputFile);
			ext = outputFile + x - 4; // get extension of file name

			if(strcmp(ext, ".jpg") == 0) outExt = 'j';
			else
			{
				cerr << "Must use '.jpg' as output file." << endl;
				Usage(argc, argv);
			}
		}

		if(inExt == 'j')
			readJpg(inputFile, v);
		else
			readBitmap(inputFile);

		writeJpg(outputFile, g, p);
		if(gMsgBuffer != NULL)
		{
			free(gMsgBuffer);
		}
		printf("\n\nStorage Capacity: %d bits (%d bytes)\nMessage Size: %d bytes\n", gBitCapacity, gBitCapacity/8, gMsgSize);
		if( (gBitCapacity/8) < gMsgSize) printf("\n\nWARNING! ENTIRE MESSAGE WAS NOT HIDDEN!!!\n\n");
		return(SUCCESS);
	} // if hiding

	// Extracting and/or Wiping or Destroying
	if(gExtractMsg || gWipeMsg || gDestroyMsg)
	{
		if(inExt != 'j')	// Input MUST be jpg
		{
			cerr << "MUST have '.jpg' file as input." << endl;
			Usage(argc, argv);
		} // input must be .jpg

		fptr = fopen(inputFile, "rb");
		if(fptr == NULL)
		{
			printf("Could not open input file %s\n\n", inputFile);
			exit(1);
		}

		// treat DC coefficeint a bit differently
		// this calculates lg2 of quality factor less hiding in DC coeffcients
		lgQ = log( (double) gImageQuality)/lg2; // lgQ==1 will nullify effect
		lgQ = 2/lgQ;

		// initialize output buffer static variables
		putBitsInBuffer(0, 0, NULL, 0);

		fileno = _fileno(fptr);
		size = (int) _filelength(fileno) + 260;	// get length of input jpg for max size of message
												// the 260 is for the possible length of the filename
		gMsgBuffer = (char *) malloc(size);
		if(gMsgBuffer == NULL)
		{
			printf("Could not allocate memory for message file.\n\n");
			exit(1);
		}
		fclose(fptr); // no longer want input file open
		memset(gMsgBuffer, 0, size);
		gMsgSize = size;

		// if output file specified
		if(outputFile != NULL)
		{
			x = (int) strlen(outputFile);
			ext = outputFile + x - 4; // get extension of file name
			if(strcmp(ext, ".bmp") == 0) outExt = 'b';
			else if(strcmp(ext, ".jpg") == 0) outExt = 'j';
			else
			{
				cerr << "Must use '.bmp' or '.jpg' as output files." << endl;
				Usage(argc, argv);
			}
		}

		// if no output file name
		if(outputFile == NULL && (gWipeMsg || gDestroyMsg) )
		{
			outputFile = gOutputFileName;		// overwrite original file
			strcpy(gOutputFileName, inputFile);
		}

		readJpg(inputFile, v);

		if(gWipeMsg || gDestroyMsg)
			writeJpg(outputFile, g, p);

		if(gExtractMsg && gMsgSize > 0) writeMsg();

		printf("\n\nStorage Capacity: %d bits (%d bytes)\nMessage Size: %d bytes\n", gBitCapacity, gBitCapacity/8, gMsgSize);
		if( (gBitCapacity/8) < gMsgSize) printf("\n\nWARNING! ENTIRE MESSAGE WAS NOT EXTRACTED!!!\n\n");
	} // if extracting, wiping, or destroying

	return(SUCCESS);
} // main
