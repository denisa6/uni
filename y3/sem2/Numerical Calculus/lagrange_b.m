﻿function f = lagrange_b(xi, fi, x)
    n = length(xi);
    w = ones(1, n);
    for j = 1:n
        w(j) = prod(xi(j) - xi([1:j-1, j + 1: n]));
    end
    w = 1./w;
    num = zeros(size(x));
    den = num;
    exact = den;
    for j = 1 : n
        xdiff = x - xi(j);
        term = w(j)./xdiff;
        num = num + fi(j) * term;
        den = den + term;
        exact(xdiff == 0) = j;
    end
    f = num./den;
    k = find(exact);
    f(k) = fi(exact(k));
end