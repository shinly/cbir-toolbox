% This function reads a siftgeo binary file
%
% Usage: [v, meta] = siftgeo_read (filename, maxdes)
%   filename    the input filename
%   maxdes      maximum number of descriptors to be loaded
%   (default=unlimited)
%
% Returned values
%   v           the sift descriptors (1 descriptor per line)
%   meta        meta data for each descriptor, i.e., per line:
%               x, y, scale, angle, mi11, mi12, mi21, mi22, cornerness
function [v, meta] = siftgeo_read (filename, maxdes)

if nargin < 2
  maxdes = 100000000;
end
  
% open the file and count the number of descriptors
fid = fopen (filename, 'r');
 
fseek (fid, 0, 1);
n = ftell (fid) / (9 * 4 + 1 * 4 + 128);
fseek (fid, 0, -1);


if n > maxdes
  n = maxdes;
end;

% first read the meta information associated with the descriptor
meta = zeros (n, 9, 'single');
v = zeros (n, 128, 'single');
d = 0;

% read the elements
for i = 1:n
  meta(i,:) = fread (fid, 9, 'float');
  d = fread (fid, 1, 'int');
  v(i,:) = fread (fid, d, 'uint8=>single');
end

fclose (fid);