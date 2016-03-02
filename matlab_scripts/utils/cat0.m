function str = cat0(src, dest_len)

str = num2str(src);
l = length(str);
if l >= dest_len
    return
end

str = [repmat('0', 1, dest_len - l), str];