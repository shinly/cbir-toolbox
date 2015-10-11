
% vladFile = 'ub_vlad64.bin';
% fid = fopen(vladFile, 'rb');
% featAll = fread(fid, inf, 'single');
% fclose(fid);
% 
dimNum = 4096;
imgNum = 10200;
% featAll = reshape(featAll, dimNum, imgNum);

searchResult = zeros(imgNum, 4);

% nsWeights = log2(4.1./(ns_scores+0.1)) + 0.1;

% NSMat = repmat(ns_scores', 4096, 1);

% matlabpool local 4;
for i = 1 : imgNum
    if mod(i, 100) == 0
        fprintf('%d\n', i);
    end
    queryFeat = repmat(featAll(:, i), 1, imgNum);
    featDis = sum(featAll .* queryFeat); % .* idfWeightMat); % weighted cosine distance
   
    [B, IX] = sort(featDis, 'descend');
    tq = floor((i - 1) / 4);

    for j = 1 : 4
        td = floor((IX(j) - 1) / 4);
        if tq == td && j < 5
            searchResult(i, j) = 1;
        end
    end
    
end
% matlabpool close;

% ns_scores = sum(searchResult, 2);
top4_score = mean(sum(searchResult(1:end,:), 2));
fprintf('Top 4 recall : %.3f\n', top4_score);

% Top 4 recall : 3.44

