function new_feats = preprocess_cnn_feats(all_feats)

org_dim = size(all_feats, 1);

fprintf('Performing L1 normalization...\n');
l1_norms = sqrt(sum(abs(all_feats)));
all_feats = sqrt(all_feats);
all_feats = all_feats./(repmat(l1_norms, org_dim, 1));

fprintf('Performing L2 normalization...\n');
l2_norms = sqrt(sum(all_feats.^2));
all_feats = all_feats./(repmat(l2_norms, org_dim, 1));

fprintf('Caculating PCA...\n');
[coff,~] = princomp(all_feats');

fprintf('Applying PCA...\n');
new_feats = (all_feats' * coff)';

fprintf('Whitening features...\n');
new_feats = white_feat(new_feats);