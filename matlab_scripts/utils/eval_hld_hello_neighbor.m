function apVec = eval_hld_hello_neighbor(relations, groundTruthVec, imgDbPath)
imgNum = 1491;
queryNum = 500;
apVec = zeros(queryNum, 1);
for i = 1 : queryNum
    if mod(i, 50) == 0
        fprintf('%d\t', i);
    end
    
    queryName = imgDbPath{i+991}(end - 9 : end - 4);
    queryImgID = sscanf(queryName, '%d') / 100;
    qn = queryImgID - 1000 + 1;
    validNum = 0;
    apVal = 0;
    for j = 2 : length(relations{i})
        if relations{i}(j) > 1491
            continue;
        end
        strName = imgDbPath{relations{i}(j)}(end - 9 : end - 4);
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
