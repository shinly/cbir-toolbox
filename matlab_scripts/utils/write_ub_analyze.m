function write_ub_analyze(f1, f2, prefix)

mm = max(f1, f2);
fid_mm = fopen([prefix, '_max.txt'], 'w');
for i = 1 : 4
    ids = find(mm==i);
    for j = 1 : length(ids)
        fprintf(fid_mm, '%d\t%d\n', ids(j)-1, i);
    end
end
fclose(fid_mm);

fid_f1 = fopen([prefix, '_f1.txt'], 'w');
gg=find(f1>f2);
for i = 1 : length(gg)
    fprintf(fid_f1, '%d\t%d\t%d\n', gg(i)-1, f1(gg(i)), f2(gg(i)));
end
fclose(fid_f1);

fid_f2 = fopen([prefix, '_f2.txt'], 'w');
ss=find(f1<f2);
for i = 1 : length(ss)
    fprintf(fid_f2, '%d\t%d\t%d\n', ss(i)-1, f1(ss(i)), f2(ss(i)));
end
fclose(fid_f2);