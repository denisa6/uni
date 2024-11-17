x=[0,3,5,8,13];
f=[0,255,383,623,993];
df=[0,77,80,74,72];
t=10;
#if you have the derivative its either hermit or bilkov
[zi,d2]=div_diff2(x,f,df);
distance=newton_int(d2,zi,10)

d=div_diff(x,df);
speed=newton_int(d,x,10)

d3=div_diff(f,df);
idk=newton_int(d3, f, distance)