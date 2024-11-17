function [x, nit]= jacobi_it(A,b,x0,maxnit,err)
    M = diag(diag(A));
    N = M-A;
    T = inv(M)*N;
    alpha = norm(T, inf);
    c = inv(M)*b;
    nit=0;
    for i=1:maxnit
        x = T*x0 + c;
        nit=nit+1;
        if norm(x-x0, inf)<err*(1-alpha)/alpha
            return
        endif
        x0 = x;
    endfor
end