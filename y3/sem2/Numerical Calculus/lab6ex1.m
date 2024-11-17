﻿lagrange([1, 2, 3], [1, 4, 9], [6, 5]);

#ex 1 a
xi = linspace(-2, 4, 10);
fi = (xi + 1)./(3*xi.^2 + 2 * xi + 1);
#ex 1 b
x = linspace(-2, 4, 500);
f = (x + 1)./(3*x.^2 + 2 * x + 1);
L9f = lagrange(xi, fi, x);
plot(x, f, x, L9f, 'g', xi, fi, 'o');

#ex 1 c
plot(x, abs(f - L9f));
max(abs(f - L9f))