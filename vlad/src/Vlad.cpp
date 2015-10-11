#include "Vlad.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;


vocab::vocab(const char *vocab_file_name, int v_dim, int v_size):
    _vocab_dim(v_dim), _vocab_size(v_size), _kmean(NULL), _centers(NULL) 
{
    ifstream is(vocab_file_name);
    if (!is.good())
    {
        cerr << "Cannot open vocabulary file " << vocab_file_name << endl;
        return;
    }
    _centers = new float[128*v_size];
    size_t base = 0;
    int id;
    for (int i = 0; i < v_size; ++i)
    {
        is >> id;
        for (int j = 0; j < 128; ++j)
        {
            is >> _centers[base + j]; 
        }
        base += 128;
    }
    _kmean = vl_kmeans_new(VL_TYPE_FLOAT, VlDistanceL2);
    vl_kmeans_set_centers(_kmean, _centers, v_dim, v_size);
    is.close();
}

vocab::~vocab()
{
	if (_kmean != NULL)
		vl_kmeans_delete(_kmean);
    if (_centers != NULL)
        delete[] _centers;
}


float* vocab::assign(float *sifts, int feature_number)
{
    vl_uint32 *indexes = new vl_uint32[feature_number];
    float *distances = new float[feature_number];
    vl_kmeans_quantize(_kmean, indexes, distances, sifts, feature_number);
    float *assignments = new float[feature_number * _vocab_size];
    memset(assignments, 0, sizeof(float) * feature_number * _vocab_size);
    for(int i = 0; i < feature_number; i++) {
        assignments[i * _vocab_size + indexes[i]] = 1.;
    }
    delete[] indexes;
    delete[] distances;
    return assignments;
}

const float* vocab::get_centers() const
{
	return _centers;
}

int vocab::size() const
{
    return _vocab_size;
}


Vlad::Vlad(const char* vocab_file_name, int vocab_size):
    _vocab(vocab_file_name, 128, vocab_size)
{

}

float* Vlad::getVlad(float* sifts, int feature_number)
{
    float *vlad = new float[128 * _vocab.size()];
    if (feature_number <= 0)
    {
        // float f = sqrt(1.0 / 128 / _vocab.size());
        for (int i = 0; i < 128 * _vocab.size(); ++i)
        {
            vlad[i] = 0;
        }
        return vlad;
    }
    float *assignments = _vocab.assign(sifts, feature_number);
    vl_vlad_encode (vlad, VL_TYPE_FLOAT, _vocab.get_centers(), 128, _vocab.size(),
        sifts, feature_number, assignments, VL_VLAD_FLAG_NORMALIZE_COMPONENTS);
    delete[] assignments;
    return vlad;
}
