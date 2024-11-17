function x = gauss_elimination(A, b)
    [r,n] = size(A);
    x = zeros(size(b));
    A = [A,b];
    # A will have A + 1 columns
    for j = 1 : n - 1
        [v, p] = max(abs(A()));
        