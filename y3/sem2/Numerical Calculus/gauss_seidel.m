function [x, nit]= gauss_seidel(A,b,x0,maxnit,err)
    L = -tril(A,-1);
    U = -triu(A,1);
    D = diag(diag(A));
    M = D - L;
    N = U;
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