clear
n = input("the number of trials = ")
p = input("give probability (between 0 & 1) = ")
N = input("give N = ")
for i = 1:N
  for j = 1:n
    X(j) = 0
    while rand >= p
      X(j) = X(j)+1;
    endwhile
  endfor
  %sum all the failures in the grometric format
  Y(i) = sum(X);
endfor
%we pretend that infinity is 150
k = 0:150;
U_Y = unique(Y);
n_Y = hist(Y,length(U_Y));
rel_freq = n_Y/N;
plot(U_Y,n_Y/N,"b*",k,nbinopdf(k,n,p),"r*")
%doesnt work for me
