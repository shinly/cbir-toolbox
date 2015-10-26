%% test match
clear;
close all;
clc;

%%
% src_1 = 'D:\Research\data\DupGroundTruthDataset\Mona Lisa\1.jpg';
% src_2 = 'D:\Research\data\DupGroundTruthDataset\Mona Lisa\489.jpg';

src_file_1 = '/var/run/media/sunshy/8ECED01BCECFF98B/files/data/Holidays/all/100000.jpg';
src_file_2 = '/var/run/media/sunshy/8ECED01BCECFF98B/files/data/Holidays/all/100001.jpg';



ext = '.siftgeo';
siftDim = 128;
%% load image and feature
im_1 = imread(src_file_1);
if max(size(im_1)) > 400
%     im_1 = imresize(im_1, 400 / max(size(im_1)));
end
im_2 = imread(src_file_2);
if max(size(im_2)) > 400
%     im_2 = imresize(im_2, 400 / max(size(im_2)));
end

%%
featPath_1 = [src_file_1, ext];
featPath_2 = [src_file_2, ext];

[SiftFeat_1, paraFeat_1] = siftgeo_read (featPath_1);
[SiftFeat_2, paraFeat_2] = siftgeo_read (featPath_2);

SiftFeat_1 = SiftFeat_1';
SiftFeat_2 = SiftFeat_2';
paraFeat_1 = paraFeat_1';
paraFeat_2 = paraFeat_2';

featNum_1 = size(SiftFeat_1, 2);
featNum_2 = size(SiftFeat_2, 2);

% normalization
SiftFeat_1 = SiftFeat_1 ./ repmat(sqrt(sum(SiftFeat_1.^2)), size(SiftFeat_1, 1), 1);
SiftFeat_2 = SiftFeat_2 ./ repmat(sqrt(sum(SiftFeat_2.^2)), size(SiftFeat_2, 1), 1);


%% Check match
normVal = mean(sqrt(sum(SiftFeat_1.^2)));
matchInd = zeros(featNum_1, 1);
matchDis = zeros(featNum_1, 1);
validDis = [];
gridDisVec = [];
ic = 0;
for i = 1 : featNum_1
    tmpFeat = repmat(SiftFeat_1(:, i), 1, featNum_2);
%     d = 1 - sum(min(tmpFeat, corrFeat_2));
    d = (sum((tmpFeat - SiftFeat_2).^2)) / normVal;
    matchDis(i) = min(d);
    [v, ind] = sort(d);
    
%    
%     if length(v) > 5 && v(5) < 0.35
% %         continue;
%     end
    if v(1) / v(2) <= 0.6 && v(1) < 0.35
%     if v(1) < 0.1211
        matchInd(i) = ind(1);
        ic = ic + 1;
        validDis(ic, 1 : 3) = [v(1), v(2), v(1) / v(2)];
        tmp = (SiftFeat_1(:, i) - SiftFeat_2(:, ind(1))).^2;
        tmp2 = reshape(tmp(:), 8, 16);
        gridDisVec(ic, 1 : 16) = sqrt(sum(tmp2));
    end
%     end
end
figure; stem(matchDis); ylim([0, 1.2]);
figure; stem(matchDis(find(matchInd > 0))); ylim([0, 1.2]);



%% Draw match results on RGB image
[row, col, cn] = size(im_1);
[r2, c2, n2] = size(im_2);
imgBig = zeros(max(row, r2), col + c2, 3);
imgBig(1 : row, 1 : col, :) = im_1;
imgBig(1 : r2, col + 1 : end, :) = im_2;

np = 40;
thr = linspace(0,2*pi,np) ;
Xp = cos(thr); 
Yp = sin(thr);

paraFeat_2(1, :) = paraFeat_2(1, :) + col;

figure(1); imshow(uint8(imgBig)); axis on;
hold on;
for i = 1 : featNum_1
    if matchInd(i) > 0
        xys =  paraFeat_1(:, i);
        xys2 = paraFeat_2(:, matchInd(i));
        figure(1);
%         figure(1); clf; imshow(uint8(imgBig));
        hold on;
        plot(xys(1), xys(2), 'ro');
        plot(xys2(1), xys2(2), 'ro');
        hold on; plot([xys(1), xys2(1)], [xys(2), xys2(2)], '-g');
        
        figure(2);
        clf;
        subplot(311); stem(SiftFeat_1(:, i)); xlim([0, 128]); ylim([0, 0.5]);
        subplot(312); stem(SiftFeat_2(:, matchInd(i))); xlim([0, 128]); ylim([0, 0.5]);
        tmp = SiftFeat_1(:, i) - SiftFeat_2(:, matchInd(i));
        subplot(313); stem(tmp); xlim([0, 128]); 
        disVal = sum(sqrt(tmp.^2));
        ylim([0, 0.2]);
    end
end
title(sprintf('total match number : %d (%d-%d)', length(find(matchInd)), featNum_1 ,featNum_2));
hold off;