f = @(x) 
[I, g_nodes, g_coeff] = gauss_quad(@(x) (x.^2+1)./(x.^2+1),2,3);
I