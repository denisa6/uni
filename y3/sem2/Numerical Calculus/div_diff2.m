function [z,tb] = div_diff2(x, f, df)
    n = length(x);
    z = repelem(x, 2);
    tb = zeros(2 * n);
    tb(:, 1) = repelem(f, 2)';
    tb(1 : 2 : 2 * n - 1, 2) = df';
    tb(2 : 2 : 2 * n - 2, 2) = (diff(f)./diff(x))';
    for j = 3:2*n
        tb(1 : 2 * n - j + 1, j) = diff(tb(1 : 2 * n - j + 2, j - 1))./(z(j : 2 * n) - z(1 : 2 * n - j + 1))';
    end
end