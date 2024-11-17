function tb = backward_diff(f)
    n = length(f);
    tb = zeros(n);
    tb(:, 1) = f';
    for j = 2 : n
        tb(j : n, j) = diff(tb(j-1:n, j - 1));
    end
end