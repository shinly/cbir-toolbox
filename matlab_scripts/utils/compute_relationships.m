function [relationships, similarities, rank_lists] = compute_relationships(features)
[~, num] = size(features);

% matlabpool local 4;

preserve_number = 100;

relationships = zeros(num, num);
similarities = zeros(num, preserve_number);
rank_lists = zeros(num, preserve_number);

for i = 1 : num
    query_feat = repmat(features(:, i), 1, num);
    sims = sum(query_feat .* features);
    [rsims, IX] = sort(sims, 'descend');
    similarities(i, :) = rsims(1:preserve_number);
    rank_lists(i, :) = IX(1:preserve_number);
	relationships(i, IX) = 1:num;
end