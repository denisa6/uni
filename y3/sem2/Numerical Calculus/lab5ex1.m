# eye(n) - identity matrix of size n
[A, b] = get_matrix(1000);
x0 = zeros(size(b));
#[x, nit] = jacobi_it(A, b, x0, 1000, 10^-5)
[x, nit] = gauss_seidel(A, b, x0, 1000, 10^-5)