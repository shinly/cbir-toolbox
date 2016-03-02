function expanded_features = dbexpansion_nn(features, relationships, similarities, rank_lists, k, cutoff, base_weight, cdms, fix_rn)

expanded_features = zeros(size(features));

[dim, num] = size(features);

for i = 1 : num
    neighbor_hoods = ones(1, k-2+1);
    if fix_rn == 0
        for j = 2 : k
            rn = max(relationships(rank_lists(i,j),i),j) - 1;
            if rn > cutoff
                neighbor_hoods(j-1) = 0;
            else
                neighbor_hoods(j-1) = 1-(rn-1)/(cutoff-1);
            end
        end
    end

    weights = base_weight .* neighbor_hoods .* similarities(i,2:k) .* cdms(rank_lists(i,2:k));
    
    weights = repmat(weights, dim, 1);
   
    expanded_features(:, i) = features(:, i) + sum(weights .* features(:,rank_lists(i,2:k)), 2);
end

expanded_features = norm_feature(expanded_features, 'L2');