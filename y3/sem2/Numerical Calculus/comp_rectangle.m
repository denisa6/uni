﻿function I = comp_rectangle(f, a, b, n)
    h = (b-a)/n;
    I = h*sum(f(a+([0:n-1] + 1/2) * h));
end