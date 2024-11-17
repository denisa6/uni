#ex1
xi=[0, 1/3, 1/2, 1];
fi=cos(pi*xi);
d=div_diff(xi, fi);
xx=linspace(0, 1, 100);
plot(xx, cos(pi*xx), xx, newton_int(d, xi, xx));

# d
res = cos(pi/5)
newton_int(d,xi,1/5)