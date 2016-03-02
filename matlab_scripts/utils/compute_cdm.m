function cdm = compute_cdm(features, K)

[~, feature_number] = size(features);

cdm = zeros(1, feature_number);

parfor i = 1 : feature_number
    queryFeat = repmat(features(:, i), 1, feature_number);
    featDis = sum(features .* queryFeat);
    [scores, ~] = sort(featDis, 'descend');
    dists = sqrt(max(0,2-2*scores(2:K)));
    cdm(i) = sum(dists);
end