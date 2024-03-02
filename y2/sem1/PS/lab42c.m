clear
p = input("give probability = ")
N = input("number of simulations = ")
for i = 1:N
  X(i) = 0;
  while rand >= p
    X(i) = X(i) + 1;
  endwhile
endfor
%we pretend that infinity in 20
k = 0:20;
U_X = unique(X);
n_X = hist(X,length(U_X));
rel_freq = n_X/N;
plot(U_X,n_X/N,"b*",k,geopdf(k,p),"r*");
legend("simulation","geo_distrib");
