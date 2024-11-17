function f = newton_int(d, xi, x)
    for k = 1 : length(x)
        res = x(k) - xi;
        c = zeros(1, length(res));
        c(1) = 1;
        for i = 1 : length(res)
            c(i+1) = c(i) .* res(i);
        end
        f(k) = c(1:end-1) * d(1,:)'; 
    end
end