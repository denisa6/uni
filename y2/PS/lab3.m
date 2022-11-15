%we are solving the first ex for the normal law
m = input ("m = ")
s = input ("s = ")
alpha = input ("alpha = ")
beta = input ("beta = ")

%we are solving 1.a
P1a = normcdf(0,m,s)
P2a = 1 - P1a

%we are solving 1.b
P1b = normcdf(1,m,s)-normcdf(-1,m,s)
P2b = 1 - P1b

%1.c
P1c = norminv(alpha,m,s)

%1.d
P1d = norminv(1-beta,m,s)

% need to do it for 3 diff laws (change the prefix of the functions) - Student - Fischer - Chi square
% change variables:
% ex: for Student cahnge m in t?



