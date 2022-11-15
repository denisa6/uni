%ex 2
p = input("give a number between 0 and 1 = ");
n = input("give a sample size = ");
u = rand(1,n);
x = (u<p);
%U_X unique values of X
u_x = unique(x); %first line of r.v X
n_x = hist(x,length(u_x)) % <-how many 0 and 1 I get
rel_freq = n_x/n;

