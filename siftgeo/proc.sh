infile=$1
tmpfile=${infile}.pgm
outfile=${infile}.siftgeo
if [ ! -f "$outfile" ]
then
	touch "$outfile"
	djpeg "$infile" | ppmtopgm | pnmnorm -bpercent=0.01 -wpercent=0.01 -maxexpand=400 | pamscale -pixels $[1024*1024] > "$tmpfile"
	./compute_descriptors_linux64 -i "$tmpfile" -o4 "$outfile" -hesaff -sift
	rm "$tmpfile" #uncomment this line if you want to reserve the pgm files
	/home/sunshy/workspace/cpp/vlad/bin/vlad $outfile
else
	echo "$outfile exists"
fi 
