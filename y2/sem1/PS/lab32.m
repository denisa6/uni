% lab 3 ex 2 Poisson
n = input("n = ")
p = input("p = ")
lambda = n*p
k = 0:1:n
resultB = binopdf(k,n,p)
resultP = poisspdf(k,lambda)
plot(k,resultB,'b')
hold on
plot(k,resultP,'r')

