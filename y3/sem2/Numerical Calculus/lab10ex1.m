f = @(x) 1./x;
comp_rectangle(f, 1, 2, 18)
log(2)

f = @(x) 1./x;
comp_trapezoid(f, 1, 2, 25)

f = @(x) 1./x;
simpsons(f, 1, 2, 10)