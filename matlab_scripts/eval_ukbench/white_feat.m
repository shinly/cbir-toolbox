function x = white_feat(feat)

x = feat;
x_energy = sqrt(sum(x'.^2))';
x = x./repmat(x_energy,1,size(x,2));
x_energy = sqrt(sum(x.^2));
x = x./repmat(x_energy,size(x,1),1);