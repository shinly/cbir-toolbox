function [SiftFeat, paraFeat] = hsift_read (filename)
siftDim = 128;
fid = fopen(filename, 'rb');
featNum = fread(fid, 1, 'int32');
SiftFeat = zeros(siftDim, featNum);
paraFeat = zeros(4, featNum);
for i = 1 : featNum
    SiftFeat(:, i) = fread(fid, siftDim, 'uchar');
    paraFeat(:, i) = fread(fid, 4, 'float32');
end
fclose(fid);