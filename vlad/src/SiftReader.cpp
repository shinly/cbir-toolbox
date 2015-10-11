#include "SiftReader.h"
#include <fstream>
using namespace std;

float* GeoSiftReader::read(const char* sift_file_name, int &feature_number)
{
	float *sifts = nullptr;

	ifstream is(sift_file_name, ios::binary);
	if (!is.good())
	{
		feature_number = -1;
		return sifts;
	}

	is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    feature_number = length / 168;

    if (feature_number == 0)
    {
    	return sifts;
    }

    sifts = new float[128*feature_number];

    unsigned char *feature = new unsigned char[128];
    float *metas = new float[9];
    int dim;

    size_t base = 0;

    for (int i = 0; i < feature_number; ++i)
    {
    	is.read((char *)metas, sizeof(float)*9);
    	is.read((char *)&dim, sizeof(int));
    	is.read((char *)feature, sizeof(unsigned char)*128);
    	for (int j = 0; j < 128; ++j)
    	{
    		sifts[base+j] = feature[j];
    	}
    	base += 128;
    }

    delete[] feature;
    delete[] metas;

    return sifts;
}

SiftReader *createSiftReader(SiftReaderType type)
{
	switch (type)
	{
		case GEO_SIFT_TYPE:
			return new GeoSiftReader();
		default:
			return nullptr;
	}
}