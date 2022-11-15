clear
n = input("the number of trials (for bino) = ")
p = input("the probability = ")
N = input("the number of random numbers on one line/the number of simulations = ")
for i=1:N
  U = rand(n,1);
  X(i) = sum(U<p);
endfor
k = 0:n;
U_X = unique(X);
n_X = hist(X,length(U_X));
rel_freq = n_X/N;
plot(U_X,n_X/N,"*",k,binopdf(k,n,p),"r*");
