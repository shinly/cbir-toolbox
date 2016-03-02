function all_features = read_ub_feats(root_path, feature_ext, data_type, feature_dimension)
% root_path = '/var/run/media/sunshy/8ECED01BCECFF98B/files/data/UKbench/';
% root_path = '/var/run/media/sunshy/8ECED01BCECFF98B/files/data/ukbench_inria_siftgeo/';
img_prefix = 'ukbench';

image_number = 10200;

all_features = zeros(feature_dimension, image_number);

for i = 0 : image_number - 1
    if mod(i, 1000) == 0
        fprintf('%d\n', i);
    end
    folder_path = num2str(floor(i/1000));
    img_name = num2str(i);
    full_name = '00000';
    full_name(6-length(img_name):end) = img_name;
    
    target_file_name = [root_path, folder_path, '/', img_prefix, full_name, feature_ext]; 
    
    fid = fopen(target_file_name, 'rb');
    all_features(:, i+1) = fread(fid, feature_dimension, data_type);
    fclose(fid);
end

