#include "SiftReader.h"
#include "Vlad.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	SiftReader *reader = createSiftReader(GEO_SIFT_TYPE);

	string filename(argv[1]);	
	string outputname = filename + ".vlad64";

	int dim = 64;

	int c;
	float *k = reader->read(filename.c_str(), c);

	Vlad vlad("/home/sunshy/workspace/utils/flickr60K.siftgeo_for_cudakmean.txt.cluster_centres", dim);
	float *code = vlad.getVlad(k, c);

	ofstream os(outputname, ios::binary);
	os.write((char*)code, sizeof(float)*128*dim);
	os.close();
	// for (int i = 0; i < 128 * dim; ++i)
	// {
	// 	cout << code[i] << " ";
	// }
	// cout << endl;
	return 0;
}