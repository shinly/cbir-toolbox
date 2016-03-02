function apVec = eval_hld_2feats(feature, queries, groundTruthVec, imgDbPath)
[~, imgNum] = size(feature);
queryNum = 500;
apVec = zeros(queryNum, 1);
for i = imgNum - 500 + 1 : imgNum
    if mod(i, 50) == 0
        fprintf('%d\t', i);
    end
    
    queryFeat = repmat(queries(:, i), 1, imgNum);
    featDis = sum(feature .* queryFeat);
    [~, IX] = sort(featDis, 'descend');
    
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
