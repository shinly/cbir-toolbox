function apVec = pr_hld(feature_rec, feature_pre, rec_num, groundTruthVec, imgDbPath)
[~, imgNum] = size(feature_rec);
queryNum = 500;
apVec = zeros(queryNum, 1);
for i = imgNum - 500 + 1 : imgNum
    if mod(i, 50) == 0
        fprintf('%d\t', i);
    end
    
    queryFeat = repmat(feature_rec(:, i), 1, imgNum);
    featDis = sum(feature_rec .* queryFeat);
    [~, IX] = sort(featDis, 'descend');
    
    preFeature = repmat(feature_pre(:, i), 1, rec_num);
    featDis = sum(preFeature .* feature_pre(:, IX(1: rec_num)));
    [~, IX_p] = sort(featDis, 'descend');
    IX(1: rec_num) = IX(IX_p);
    
    queryName = imgDbPath{i}(end - 9 : end - 4);
    queryImgID = sscanf(queryName, '%d') / 100;
    qn = queryImgID - 1000 + 1;
    validNum = 0;
    apVal = 0;
    for j = 2 : imgNum

        
        strName = imgDbPath{IX(j)}(end - 9 : end - 4);
        resultImgID = sscanf(strName, '%d');
        
        if queryImgID == round(resultImgID / 100) && strcmp(queryName, strName) ~= 1
            validNum = validNum + 1;
            apVal = apVal + validNum / (j - 1);
        end
    end
    if validNum > 0
        apVal = apVal / groundTruthVec(qn);
        apVec(qn) = apVal;
    end
end

mAPval = mean(apVec);
fprintf('\nMean average precision: %.4f\n', mAPval);
