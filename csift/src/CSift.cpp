// CSift.cpp : Defines the entry point for the console application.
//


#include <string>
#include <iostream>
#include "Csiftfeature.h"

using namespace std;

int main(int argc, char* argv[])
{	
	if (argc != 2 && argc != 3)
	{
		cout << "Error : no input parameters! \n";
		exit(1);
	}
	if (argc == 3 && argv[2][0] == 'p')
	{
		string imgFilePath = argv[1];
		string sift_saveFile = imgFilePath + ".pos";
		int m_imgNum = 0;
		ExtractSiftFeatureOnlyPos(imgFilePath, sift_saveFile, m_imgNum);
	}
	else
	{
		string imgFilePath = argv[1];
		string sift_saveFile = imgFilePath + ".sift";
		int m_imgNum = 0;

		ExtractSiftFeature(imgFilePath, sift_saveFile, m_imgNum);
	}
	return 0;
}

