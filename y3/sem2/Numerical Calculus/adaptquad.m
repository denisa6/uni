function I = adaptquad(f, a, b, eps, met, n)
    I1 = met(f, a, b, n);
    I2 = met(f, a, b, 2*n);
    if abs(I1 - I2) < eps
        I = I2
    else
        I = adaptquad(f, a, (a+b)/2, eps, met, n) + adaptquad(f, (a+b)/2, b, eps, met, n)
        
adaptquad(f, 0, 1, 10^-6, @simpsons, 4)        
