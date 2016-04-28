function [relationships, similarities, rank_lists, cdm] = compute_relationships(features, K)
[~, num] = size(features);

% matlabpool local 4;

preserve_number = 10;

relationships = zeros(num, num);
similarities = zeros(num, preserve_number);
rank_lists = zeros(num, preserve_number);
cdm = zeros(1, num);

for i = 1 : num
    if mod(i, 500) == 0
        fprintf('%d/%d\n', i, num);
    end
    query_feat = repmat(features(:, i), 1, num);
    sims = sum(query_feat .* features);
    [rsims, IX] = sort(sims, 'descend');
    similarities(i, :) = rsims(1:preserve_number);
    rank_lists(i, :) = IX(1:preserve_number);
	relationships(i, IX) = 1:num;
%     [~, relationships(i, :)] = sort(IX);
    dists = sqrt(max(0,2-2*rsims(2:K)));
    cdm(i) = sum(dists);
end