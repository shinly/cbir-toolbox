function all_features = read_hld_feats(root_path, images_list_file, query_list_file, feature_dimension, data_type)

% root_path = '/var/run/media/sunshy/8ECED01BCECFF98B/files/data/Holidays/';
% root_path = '/home/sunshy/Data/Holiday/';
% images_list_file = 'imagelist_conv5.txt';
% query_list_file = 'querylist_conv5.txt';
images_number = 991;
query_number = 500;
% feature_dimension = 256;
% data_type = 'single';

all_features = single(zeros(feature_dimension, images_number + query_number));

fid = fopen([root_path,images_list_file], 'r');
for i = 1 : images_number
    file_path = fgetl(fid);
    full_path = [root_path, file_path];
%     full_path(end-3:end) = 'map5';
    ff = fopen(full_path, 'rb');
    all_features(:, i) = fread(ff, feature_dimension, data_type);
    fclose(ff);
end
fclose(fid);

fid = fopen([root_path,query_list_file], 'r');
for i = 1 : query_number
    file_path = fgetl(fid);
    full_path = [root_path, file_path];
%     full_path(end-3:end) = 'mav5';
    ff = fopen(full_path, 'rb');
    all_features(:, images_number + i) = fread(ff, feature_dimension, data_type);
    fclose(ff);
end
fclose(fid);