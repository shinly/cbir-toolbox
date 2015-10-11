#pragma once

enum SiftReaderType
{
	GEO_SIFT_TYPE
};

class SiftReader
{
public:
	SiftReader() {};
	~SiftReader() {};
	
	virtual float* read(const char* sift_file_name, int &feature_number) = 0;
};

class GeoSiftReader: public SiftReader
{
public:
	
	float* read(const char* sift_file_name, int &feature_number) override;
};

SiftReader *createSiftReader(SiftReaderType type);