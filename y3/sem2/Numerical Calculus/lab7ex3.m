﻿x=linspace(1001, 1009, 9);
xi =1000:10:1050;
fi = [3.00000000, 3.0043214, 3.0086002, 3.0128372, 3.0170333, 3.0211893];
d=div_diff(xi, fi);
f = newton_int(d, xi, x)
log10(x)