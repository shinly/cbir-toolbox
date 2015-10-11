//#include "sift.h"
//#pragma comment(linker, "\"/manifestdependency:type='Win32' name='Microsoft.VC80.CRT' version='8.0.50608.0' processorArchitecture='X86' publicKeyToken='1fc8b3b9a1e18e3b' language='*'\"")

#include "imgfeatures.h"
#include "utils.h"

#include <highgui.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Csiftfeature{
public:
	// initiate the instance by inputing the image
	Csiftfeature(IplImage* in_image);

	~Csiftfeature();
	Csiftfeature();

	// the method for feature extaction
	void _extractSIFT();

	// draw the features on the image, the new image will be called as img_draw
	void _drawfeatures();

	// show the drawn image in a new window
	void _showdrawnimg();


	void _initialize(IplImage* in_image);

	// get the feature num
	int _getSIFTnum();

	// copy the SIFT features into a new arrary
	void _copySIFTarrary(simpfeature* newfeature);

	// save the feature into a file
	void _saveSIFT_Binary(string saveDir);
	void _saveSIFT_Text(string saveDir);

	// the arrary for feature storage
	feature* m_features;

	simpfeature* m_simpfea;

private:
	// the image for feature extraction
	IplImage* img;	

	// the image that have been drawn
	IplImage* img_draw;

	// the number of the sift feature
	int SIFTnum;



	int intvls;
	/** default sigma for initial gaussian smoothing */
	double sigma;
	/** default threshold on keypoint contrast |D(x)| */
	double contr_thr;
	/** default threshold on keypoint ratio of principle curvatures */
	int curv_thr;
	/** double image size before pyramid construction? */
	int img_dbl;
	/** default width of descriptor histogram array */
	int descr_width;
	/** default number of bins per histogram in descriptor array */
	int descr_hist_bins;

};


bool IsImageFile(const wchar_t * filename);
// void ExtractFolderFeatures(wstring m_SrcFolder, int &img_num);
void ExtractSiftFeature(string srcDir, string saveFile, int &m_imgNum);
void ExtractSiftFeatureOnlyPos(string srcDir, string saveFile, int &m_imgNum);

/*************************** Function Prototypes *****************************/

/**
Finds SIFT features in an image using default parameter values.  All
detected features are stored in the array pointed to by \a feat.

@param img the image in which to detect features
@param feat a pointer to an array in which to store detected features

@return Returns the number of features stored in \a feat or -1 on failure
@see _sift_features()
*/
int sift_features( IplImage* img, struct feature** feat );

IplImage* create_init_img( IplImage*, int, double );
IplImage* convert_to_gray32( IplImage* );
IplImage*** build_gauss_pyr( IplImage*, int, int, double );
IplImage* downsample( IplImage* );
IplImage*** build_dog_pyr( IplImage***, int, int );
CvSeq* scale_space_extrema( IplImage***, int, int, double, int, CvMemStorage*);
int is_extremum( IplImage***, int, int, int, int );
struct feature* interp_extremum( IplImage***, int, int, int, int, int, double);
void interp_step( IplImage***, int, int, int, int, double*, double*, double* );
CvMat* deriv_3D( IplImage***, int, int, int, int );
CvMat* hessian_3D( IplImage***, int, int, int, int );
double interp_contr( IplImage***, int, int, int, int, double, double, double );
struct feature* new_feature( void );
int is_too_edge_like( IplImage*, int, int, int );
void calc_feature_scales( CvSeq*, double, int );
void adjust_for_img_dbl( CvSeq* );
void calc_feature_oris( CvSeq*, IplImage*** );
double* ori_hist( IplImage*, int, int, int, int, double );
int calc_grad_mag_ori( IplImage*, int, int, double*, double* );
void smooth_ori_hist( double*, int );
double dominant_ori( double*, int );
void add_good_ori_features( CvSeq*, double*, int, double, struct feature* );
struct feature* clone_feature( struct feature* );
void compute_descriptors( CvSeq*, IplImage***, int, int );
double*** descr_hist( IplImage*, int, int, double, double, int, int );
void interp_hist_entry( double***, double, double, double, double, int, int);
void hist_to_descr( double***, int, int, struct feature* );
void normalize_descr( struct feature* );
int feature_cmp( void*, void*, void* );
void release_descr_hist( double****, int );
void release_pyr( IplImage****, int, int );


int import_oxfd_features( char*, struct feature** );
int export_oxfd_features( char*, struct feature*, int );
void draw_oxfd_features( IplImage*, struct feature*, int );
void draw_oxfd_feature( IplImage*, struct feature*, CvScalar );

int import_lowe_features( char*, struct feature** );
int export_lowe_features( char*, struct feature*, int );
void draw_lowe_features( IplImage*, struct feature*, int );
void draw_lowe_feature( IplImage*, struct feature*, CvScalar );

/**
Finda SIFT features in an image using user-specified parameter values.  All
detected features are stored in the array pointed to by \a feat.

@param img the image in which to detect features
@param feat a pointer to an array in which to store detected features
@param intvls the number of intervals sampled per octave of scale space
@param sigma the amount of Gaussian smoothing applied to each image level
	before building the scale space representation for an octave
@param contr_thr a threshold on the value of the scale space function
	\f$\left|D(\hat{x})\right|\f$, where \f$\hat{x}\f$ is a vector specifying
	feature location and scale, used to reject unstable features;  assumes
pixel values in the range [0, 1]
@param curv_thr threshold on a feature's ratio of principle curvatures
	used to reject features that are too edge-like
@param img_dbl should be 1 if image doubling prior to scale space
	construction is desired or 0 if not
@param descr_width the width, \f$n\f$, of the \f$n \times n\f$ array of
	orientation histograms used to compute a feature's descriptor
@param descr_hist_bins the number of orientations in each of the
	histograms in the array used to compute a feature's descriptor

@return Returns the number of keypoints stored in \a feat or -1 on failure
@see sift_features()
*/
int _sift_features( IplImage* img, struct feature** feat, int intvls,
						  double sigma, double contr_thr, int curv_thr,
						  int img_dbl, int descr_width, int descr_hist_bins );