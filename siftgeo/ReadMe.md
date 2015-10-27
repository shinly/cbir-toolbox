## Content

#### proc.sh

Shell script for hessian affine sift extracting. (for jpeg file)

Usage:
```bash
./proc.sh <jpeg_file_path>
```

#### proc_bmp.sh

Shell script for hessian-affine sift extracting. (for bmp file)

Usage:
```bash
./proc_bmp.sh <bmp_file_path>
```

#### batch.sh

A simple batch wrapper. Modify the `find` path before running.

#### compute_descriptors_linux64

The feature extracting binary programme provided by Herve Jegou. See his homepage: [http://www.irisa.fr/texmex/people/jegou](http://www.irisa.fr/texmex/people/jegou)

#### siftgeo_read.m

Matlab script for reading siftgeo binary file.

#### test_matchSIFT.m

Matlab script for feature matching between two image files. Change the `src_file_$` path before running.
