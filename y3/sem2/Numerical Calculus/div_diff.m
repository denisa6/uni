function tb = div_diff(x,f)
    n = length(x);
    tb = zeros(n);
    tb(:, 1)=f';
    for j=2:n
        tb(1:n - j + 1, j)=diff(tb(1 : n - j + 2, j - 1))./(x(j : n)-x(1 : n - j + 1))';
    end
end