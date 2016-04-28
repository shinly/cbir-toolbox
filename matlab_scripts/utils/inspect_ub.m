function inspect_ub(id, ns_org, ns_ef, res_org, res_ef)
% load('dbexpcomp.mat');

fprintf('org: %d\nuef: %d\n', ns_org(id), ns_ef(id));

ub_root = '/home/qtlab/dataset/ukbench/full/';


for i = 1 : 4
    subplot(2, 4, i), subimage(imread([ub_root, get_im_path(res_org(id, i))]));
    title(num2str(res_org(id, i)));
end
for i = 1 : 4
    subplot(2, 4, i+4), subimage(imread([ub_root, get_im_path(res_ef(id, i))]));
    title(num2str(res_ef(id, i)));
end


end

function str = get_im_path(id)
str = ['ukbench', cat0(id-1, 5), '.jpg'];
end