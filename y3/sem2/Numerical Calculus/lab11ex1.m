f = @(x) 1./(2+sin(x))
[I, ni] = romberg(f, 0, pi/2, 10^-6, 50);
ni
I
vpa(pi*sqrt(3)/9, 6)