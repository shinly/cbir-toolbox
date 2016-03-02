function write_hello_neighbor(features, query_ids, query_output_file, forward_output_file, backward_output_file)

[~, db_num] = size(features);
query_num = length(query_ids);

scores = zeros(db_num, db_num);
ranklists = zeros(db_num, db_num);
relationships = zeros(db_num, db_num);
for i = 1 : db_num
    query_feat = repmat(features(:, i), 1, db_num);
    similarities = sum(query_feat .* features);
    
    [sorted, IX] = sort(similarities, 'descend');
    scores(i, :) = sorted;
    ranklists(i, :) = IX;
	relationships(i, IX) = 1:db_num;
end
fprintf('finished computing relationships.\n');

fid = fopen(query_output_file, 'wb');
fwrite(fid, query_num, 'uint32');
for i = 1 : query_num
    fwrite(fid, i, 'uint32');
    fwrite(fid, db_num, 'uint32');
    for j = 1 : db_num
        fwrite(fid, scores(query_ids(i), j), 'single');
        fwrite(fid, ranklists(query_ids(i),j), 'uint32');
    end
end
fclose(fid);
fprintf('finished writing query.\n');

fid = fopen(forward_output_file, 'wb');
fwrite(fid, db_num, 'uint32');
for i = 1 : db_num
    fwrite(fid, i, 'uint32');
    fwrite(fid, db_num, 'uint32');
    for j = 1 : db_num
        fwrite(fid, scores(i, j), 'single');
        fwrite(fid, ranklists(i,j), 'uint32');
    end
end
fclose(fid);
fprintf('finished writing forward.\n');

fid = fopen(backward_output_file, 'wb');
fwrite(fid, db_num, 'uint32');
for i = 1 : db_num
    fwrite(fid, i, 'uint32');
    fwrite(fid, db_num, 'uint32');
    for j = 1 : db_num
        fwrite(fid, relationships(j, i), 'uint32');
        fwrite(fid, ranklists(i,j), 'uint32');
    end
end
fprintf('finished writing backword.\n');