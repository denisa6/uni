﻿#exercise 2
xi = 1980:10:2020;
fi = [4451 5287 6090 6970 7821];
y = lagrange_b(xi, fi, [2005, 2015]);
abs(y - [6474, 7405])./abs([6474, 7405]);

# ex3
fi = [10, 11, 12];
xi = [100, 121, 144];
lagrange_b(xi, fi, [118])
sqrt(118)