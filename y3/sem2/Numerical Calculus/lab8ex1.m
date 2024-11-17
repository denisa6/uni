xi=[0,1,2];
fi=1./(1+x);
d=div_diff(xi,fi);
xx=linspace(0,2,100);
Lf=newton_int(d,xi,xx);
plot(xx,Lf);

dfi=-1./(1+x).^2;
[zi,dz]=div_diff2(xi,fi,dfi);
Hf=newton_int(dz,zi,xx);
hold on;
plot(xx,Hf);