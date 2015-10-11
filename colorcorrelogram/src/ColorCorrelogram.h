#pragma once
#include <cv.h>
#include "ColorQuantization.h"

#define Num_ColorBin 32 //* quantized to 32 colors */
#define Distance_Range 10 //* distance range to calculate in correlogram *//

using namespace std;
class ColorCorrelogram
{
private:
	IplImage* h_plane;
	IplImage* s_plane;
	IplImage* v_plane;

	IplImage* quantized;

public:
    double correlogram[Num_ColorBin][Distance_Range];
	int pixelNum[Num_ColorBin];

public:
	ColorCorrelogram(IplImage** planes);
	~ColorCorrelogram(void);
	void calcCorrelogram();
};

