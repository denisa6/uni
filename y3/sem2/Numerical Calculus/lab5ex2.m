A=[10,7,8,7;7,5,6,5;8,6,10,9;7,5,9,10];
b=[32,23,33,31]';

#a
x=A\b

#b
bp=[32.1, 22.9, 33.1, 30.9]';
xp = A\bp

#c
Ap=[10,7,8.1,7.2;7.8,5.04,6,5;8,5.98,9.89,9;6.99,4.99,9,9.98];
xap = Ap\b
inerr = norm(b-bp)/norm(b)
outerr = norm(x-xp)/norm(x)
norm(A-Ap)/norm(A)

cond(A)