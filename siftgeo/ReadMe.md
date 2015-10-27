## Content

1. proc.sh

Shell script for hessian affine sift extracting. (for jpeg file)

Usage:

./proc.sh <jpeg_file_path>

2. proc_bmp.sh

Shell script for hessian-affine sift extracting. (for bmp file)

Usage:

./proc_bmp.sh <bmp_file_path>


3. batch.sh

A simple batch wrapper. Modify the `find` path before running.

4. compute_descriptors_linux64

The feature extracting binary programme provided by Herve Jegou. See his homepage: [http://www.irisa.fr/texmex/people/jegou](http://www.irisa.fr/texmex/people/jegou)

5. siftgeo_read.m

Matlab script for reading siftgeo binary file.

6. test_matchSIFT.m

Matlab script for feature matching between two image files. Change the `src_file_$` path before running.
