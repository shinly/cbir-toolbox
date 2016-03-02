function [query_list, retrieval_list, score_list] = read_hello_neighbor(inputfile)

fid = fopen(inputfile, 'rb');
size = fread(fid, 1, 'uint32');

query_list = zeros(size, 1);
retrieval_list = cell(size, 1);
score_list = cell(size, 1);

for i = 1 : size
     query_list(i) = fread(fid, 1, 'uint32');
%     assert(id == i);
    length = fread(fid, 1, 'uint32');
    retrieval_list{i} = zeros(1, length);
    score_list{i} = zeros(1, length);
    for j = 1 : length
        score_list{i}(j) = fread(fid, 1, 'single');
        retrieval_list{i}(j) = fread(fid, 1, 'uint32');
    end
end