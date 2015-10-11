#include "ColorCorrelogram.h"
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <queue>

using namespace std;
using namespace cv;

ColorCorrelogram::ColorCorrelogram(IplImage** planes)
{
	h_plane=planes[0];
	s_plane=planes[1];
	v_plane=planes[2];

	quantized=cvCreateImage( cvGetSize(h_plane), 8, 1 );
	cvZero(quantized);

	for(int i=0;i<Num_ColorBin;i++)
	{
		for(int j=0;j<Distance_Range;j++)
		{
			correlogram[i][j]=(double)0.0;
		}
		pixelNum[i]=0;
	}

	ColorQuantizition(planes,quantized);
}

ColorCorrelogram::~ColorCorrelogram(void)
{
}

void ColorCorrelogram::calcCorrelogram()
{
	int height=h_plane->height;
	int width=h_plane->width;
	int stepwidth=h_plane->widthStep;


	for(int pi=0;pi<height;pi++)
	{
		for(int pj=0;pj<width;pj++)
		{
			int color=*(quantized->imageData+pi*stepwidth+pj);
			pixelNum[color]++;

			for(int d=1;d<=Distance_Range;d++)
			{
				int sameColorNum=0; //* number of pixels with same color in the d-distance boundary */
				int totalBoundaryNum=0; //* total number of pixels in the d-distance boundary */

				//* up boundary */
				for(int i=pi-d,j=pj-d;j<=pj+d;j++)
				{
					if(i<0)
						break;
					if(j<0||j>=width)
						continue;
					int color2=*(quantized->imageData+i*stepwidth+j);
					if(color==color2)
					{
						sameColorNum++;
					}
					totalBoundaryNum++;
				}
				//* down boundary */
				for(int i=pi+d,j=pj-d;j<=pj+d;j++)
				{
					if(i>=height)
						break;
					if(j<0||j>=width)
						continue;
					int color2=*(quantized->imageData+i*stepwidth+j);
					if(color==color2)
					{
						sameColorNum++;
					}
					totalBoundaryNum++;
				}
				//* left boundary */
				for(int i=pi-d+1,j=pj-d;i<=pi+d-1;i++)
				{
					if(j<0)
						break;
					if(i<0||i>=height)
						continue;
					int color2=*(quantized->imageData+i*stepwidth+j);
					if(color==color2)
					{
						sameColorNum++;
					}
					totalBoundaryNum++;
				}
				//* up boundary */
				for(int i=pi-d+1,j=pj+d;i<=pi+d-1;i++)
				{
					if(j>=width)
						break;
					if(i<0||i>=height)
						continue;
					int color2=*(quantized->imageData+i*stepwidth+j);
					if(color==color2)
					{
						sameColorNum++;
					}
					totalBoundaryNum++;
				}
				if(totalBoundaryNum!=0)//* Not necessary practically, only used when there is only one pixel in the image */ 
				{
					correlogram[color][d-1]+=(double)sameColorNum/(double)totalBoundaryNum;
				}
			}
		}
	}
	for(int c=0;c<Num_ColorBin;c++)
	{
		for(int d=0;d<Distance_Range;d++)
		{
			//* if the color doesn't show up in the image, the default relative probability would be set 0 (need more study)*/
			if(pixelNum[c]!=0)
				correlogram[c][d]=correlogram[c][d]/(double)pixelNum[c];
		}
	}
	// cout<<"distance";
	// for(int i=0;i<Distance_Range;i++)
	// {
	// 	cout<<"\t"<<i+1;
	// }
	// cout<<endl<<endl<<"color"<<endl<<endl;
	// for(int i=0;i<Num_ColorBin;i++)
	// {
	// 	cout<<i<<":\t";
	// 	for(int j=0;j<Distance_Range;j++)
	// 	{
	// 		if(correlogram[i][j]<0)//* To avoid problem caused by : 0 is presented by a very small number in type of double */
	// 			cout<<"\t"<<0;
	// 		else
	// 			printf("\t%.5lf",correlogram[i][j]);
	// 	}
	// 	cout<<endl<<endl;	
	// }
}