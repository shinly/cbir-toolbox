function ns = ukb_ns_cdm(features, cdms)
imgNum = 10200;
% featAll = reshape(featAll, dimNum, imgNum);

searchResult2 = zeros(imgNum, 4);
% similarity = zeros(imgNum, imgNum);
% nsWeights = log2(4.1./(ns_scores+0.1)) + 0.1;

% NSMat = repmat(ns_scores', 4096, 1);
% matlabpool local 4;
parfor i = 1 : imgNum
    if mod(i, 1000) == 0
        fprintf('%d\t', i);
    end
    queryFeat = repmat(features(:, i), 1, imgNum);
%     featDis = sum(features .* queryFeat); % .* idfWeightMat); % weighted cosine distance
%     [~, IX] = sort(featDis, 'descend');

    featDis = sum((queryFeat - features).^2) ./ cdms;
    [~, IX] = sort(featDis);
    tq = floor((i - 1) / 4);

    for j = 1 : 4
        td = floor((IX(j) - 1) / 4);
        if tq == td && j < 5
            searchResult2(i, j) = 1;
        end
    end
%     similarity(i, :) = B;
    
end
fprintf('\n');
% matlabpool close;

ns = sum(searchResult2(1:end,:), 2);
% ns_scores = sum(searchResult, 2);
top4_score = mean(ns);
fprintf('Top 4 recall : %.3f\n', top4_score);

% Top 4 recall : 3.44

