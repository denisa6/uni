xi=-4:4;
x=1/2;
fi=2 .^ xi;


P = zeros(length(xi));
for i = 1:length(xi)
    P(i, 1) = fi(i);
end 
for i = 1:length(xi)
    for j = 1:i-1
        P(i, j+1) = ((x - xi(j))*P(i, j) - (x - xi(i))*P(j, j))/(xi(i)-xi(j));
    end
end
P
sqrt(2)