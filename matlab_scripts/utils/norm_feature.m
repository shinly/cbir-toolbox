function normed = norm_feature(feature, type)

[dim, ~] = size(feature);

if strcmp(type, 'L2')
    fprintf('L2\n');
    normed = feature ./ repmat(sqrt(sum(feature.^2)), dim, 1);
elseif strcmp(type, 'ROOT')
    fprintf('ROOT\n');
    normed = sqrt(feature ./ repmat(sum(feature), dim, 1));
else
    error(['unrecognized parameter type ', type, '. options are L2 or ROOT']);
end
    