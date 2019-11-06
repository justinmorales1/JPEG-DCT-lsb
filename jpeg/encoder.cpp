#include "../include/Hide.h"

using namespace std ;

void Enc_Progress (BitmapImageCoder &coder,
               void *data,
               unsigned int currentpass,
               unsigned int passcount,
               unsigned int progress,
               bool &cancel)
{
  cout << currentpass << " of " << passcount << " " << progress << "%             \r" << flush ;
  return ;
}

void Dec_Progress (BitmapImageCoder &coder,
               void *data,
               unsigned int currentpass,
               unsigned int passcount,
               unsigned int progress,
               bool &cancel)
{
  cout << currentpass << " of " << passcount << " " <<  progress << "%           \r" << flush ;
  return ;
}

// reads a bitmap into gImage object
int readBitmap(char *inputFile)
{
	ifstream input (inputFile, ios::binary) ;
	if (! input)
	{
		cerr << "Can't open input file " << inputFile << endl ;
		return 1 ;
	}

	try
	{
		gBitmapDecoder.ReadImage (input, gImage) ; // reading bmp into image object
	}
	catch (exception &ee)
	{
		cerr << ee.what () << endl ;
		return 1 ;
	}

	return(SUCCESS);
} // readBitmap

// reads a jpg into gImage object
int readJpg(char *inputFile, bool v)
{
	if(v) gJpgDecoder.SetVerbose (true) ;

	gJpgDecoder.SetProgressFunction (Dec_Progress, NULL) ;

	ifstream is (inputFile, ios::binary) ;
	if (! is)
	{
		cerr << "Can't open input file " << inputFile << endl ;
		return 1 ;
	}

	cout << "Reading Image..." << endl ;
	try
	{
		gJpgDecoder.ReadImage (is, gImage); // reading a jpg into image object
	}
	catch (EGraphicsException &ee)
	{
		cerr << ee.what () << endl << flush ;
		return 1 ;
	}

	return(SUCCESS);
} // readJpg

// writes a gImage object to Bitmap
int writeBitmap(char *outputFile)
{
	cout << "Writing Output..." << endl ;
	ofstream os (outputFile, ios::binary|ios::trunc) ;
	if (! os)
	{
		cerr << "Can't open output file " << outputFile << endl ;
		return 1 ;
	}

	try
	{
  		gBitmapEncoder.WriteImage (os, gImage); // writing image object to bitmap
	}
	catch (EGraphicsException &ee)
	{
		cerr << ee.what () << endl << flush ;
		return 1 ;
	}
	cout << "Done..." << endl << flush ;

	return(SUCCESS);
} // writeBitmap

// writes a gImage object to jpg
int writeJpg(char *outputFile, bool g, bool p)
{
	gJpgEncoder.SetProgressFunction (Enc_Progress, NULL) ;
	gJpgEncoder.SetQuality(gImageQuality);

	// Change the default. Place each component in a separate scan.
	gJpgEncoder.SetScanAttributes (0, 2, 0, 0) ;
	gJpgEncoder.SetScanAttributes (1, 4, 0, 0) ;
	gJpgEncoder.SetScanAttributes (2, 8, 0, 0) ;

	if(g) gJpgEncoder.SetGrayscale (true) ;
	if(p) gJpgEncoder.SetProgressive (true) ;

	ofstream output (outputFile, ios::binary|ios::trunc) ;
	if (! output)
	{
		cerr << "Can't open output file " << outputFile << endl ;
		return 1 ;
	}

	// output the image
	try
	{
		gJpgEncoder.WriteImage (output, gImage) ; // writing image object to jpg
	}
	catch (exception &ee)
	{
		cerr << ee.what () << endl ;
		return (FAILURE);
	}
	return(SUCCESS);
} // writeJpg

