#pragma once

#include "kmeans.h"
#include "vlad.h"

class vocab
{
public:
	vocab(const char *vocab_file_name, int v_dim, int v_size);
	virtual ~vocab();

	float* assign(float *sifts, int feature_number);

	const float* get_centers() const;
	int size() const;

private:
	int _vocab_dim;
	int _vocab_size;

	VlKMeans* _kmean;
	float* _centers;
};


class Vlad
{
public:
	Vlad(const char* vocab_file_name, int vocab_size);
	~Vlad() {}
	
	float* getVlad(float* sifts, int feature_number);
private:
	vocab _vocab;
};
