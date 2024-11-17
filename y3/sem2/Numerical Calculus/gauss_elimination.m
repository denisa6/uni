function x = gauss_elimination(A, b)
    [r,n] = size(A);
    x = zeros(size(b));
    A = [A,b];
    # A will have A + 1 columns
    for j = 1 : n - 1
        [v, p] = max(abs(A(:,j)));
        p
        #swap rows
        for i = j+1:r
            #m=A(i, ) / A();
            #A(i,) = A(i,) - m*A();
        end
    end
    x = backsubst(A(:,1:n),A(:,n+1));
end      