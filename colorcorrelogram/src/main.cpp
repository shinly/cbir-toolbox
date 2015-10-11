#include "ColorCorrelogram.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace cv;
using namespace std;

void smooth(IplImage* plane)
{
	for(int i=1;i<plane->height-1;i++)
	{
		for(int j=1;j<plane->width-1;j++)
		{
			char target=*(plane->imageData+i*plane->widthStep+j);
			char left=*(plane->imageData+i*plane->widthStep+j-1);
			char right=*(plane->imageData+i*plane->widthStep+j+1);
			char up=*(plane->imageData+(i-1)*plane->widthStep+j);
			char down=*(plane->imageData+(i+1)*plane->widthStep+j);
			char upleft=*(plane->imageData+(i-1)*plane->widthStep+j-1);
			char upright=*(plane->imageData+(i-1)*plane->widthStep+j+1);
			char downleft=*(plane->imageData+(i+1)*plane->widthStep+j-1);
			char downright=*(plane->imageData+(i+1)*plane->widthStep+j+1);
			*(plane->imageData+i*plane->widthStep+j)=(target*8+left+right+up+down+upleft+upright+downleft+downright)/16;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <image_file_name>" << endl;
		return 1;
	}


	string outfile_name = argv[1];
	outfile_name += ".color";

	ofstream out_file(outfile_name.c_str(), ios::binary);
	if (!out_file.good())
	{
		cerr << "!! Failed to open save file " << outfile_name << " for writing !!" << endl;
		return -2;
	}

	Mat frame = imread(argv[1]);
	if (!frame.data)
	{
		cerr << "!!Failed to read image file " << argv[1] << " !!" << endl;
	}

	int cols = frame.cols;
	int rows = frame.rows;
	int max_len = 640;
	if (cols > max_len || rows > max_len)
	{
		double scale;

		if (rows > cols)
		{
			scale = max_len / (rows + 0.0) ;
		}
		else
		{
		 	scale = max_len / (cols + 0.0);
		}
		Mat dest;
		resize(frame, dest, Size(cols*scale, rows*scale), 0, 0, INTER_NEAREST);
	}

	IplImage pImg = IplImage(frame);

	//* convert to HSV */
	IplImage* hsv = cvCreateImage( cvGetSize(&pImg), 8, 3 );
	IplImage* h_plane = cvCreateImage( cvGetSize(&pImg), 8, 1 );
	IplImage* s_plane = cvCreateImage( cvGetSize(&pImg), 8, 1 );
	IplImage* v_plane = cvCreateImage( cvGetSize(&pImg), 8, 1 );
	IplImage* planes[] = { h_plane, s_plane , v_plane };

	cvCvtColor( &pImg, hsv, CV_BGR2HSV );
	cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

	ColorCorrelogram* correlogram=new ColorCorrelogram(planes);
	correlogram->calcCorrelogram();
	cvReleaseImage(&hsv);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);

	float* feat = new float[Num_ColorBin*Distance_Range];
	double energy = 0.0;

	for (int i = 0; i < Num_ColorBin; ++i)
	{
		for (int j = 0; j < Distance_Range; ++j)
		{
			energy += correlogram->correlogram[i][j] * correlogram->correlogram[i][j];
			// cout << correlogram->correlogram[i][j] << " ";
		}
		// cout << endl;
	}
	energy = sqrt(energy);
	// cout << "energy: " << energy << endl;
	size_t base = 0;

	for (int i = 0; i < Num_ColorBin; ++i)
	{
		for (int j = 0; j < Distance_Range; ++j)
		{
			feat[base+j] = correlogram->correlogram[i][j] / energy;
		}
		base += Distance_Range;
	}
	out_file.write((char*)feat, sizeof(float)*Num_ColorBin*Distance_Range);

	delete[] feat;
	out_file.close();
	delete correlogram;
	return 0;
}
