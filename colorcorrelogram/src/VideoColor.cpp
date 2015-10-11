// VideoColor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ColorCorrelogram.h"
#include <opencv.hpp>
#include <iostream>
#include <fstream>
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
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <video_name> <save_file_name>" << endl;
		return 1;
	}

	VideoCapture cap(argv[1]);
	if (!cap.isOpened())
	{
		cout << "!! Failed to open video file " << argv[1] << " !!" << endl;
		return -1;
	}

	ofstream out_file(argv[2], ios::binary);
	if (!out_file.good())
	{
		cout << "!! Failed to open save file " << argv[2] << " for writing !!" << endl;
		return -2;
	}

	Mat frame;
	cap.read(frame);
	size_t frame_idx = 0;

	size_t frame_data_len = frame.cols * frame.rows;
	size_t rows = frame.rows;
	size_t cols = frame.cols;

	out_file.write((char *)&cols, sizeof(int));
	out_file.write((char *)&rows, sizeof(int));

	cap.set(CV_CAP_PROP_POS_FRAMES, 0);

	for (;;)
	{
		if (!cap.read(frame))
		{
			break;
		}

		if (frame_idx++ % 25 != 0)
		{
			continue;
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
		delete correlogram;
		cvReleaseImage(&hsv);
		cvReleaseImage(&h_plane);
		cvReleaseImage(&s_plane);
		cvReleaseImage(&v_plane);

		for (int i = 0; i < Num_ColorBin; ++i)
		{
			out_file.write((char *)correlogram->correlogram[i], Distance_Range * sizeof(double));
		}

		cout << frame_idx << "\r";

	}

	cout << endl << "# frames: " << frame_idx << endl;

	out_file.close();
	return 0;
}
