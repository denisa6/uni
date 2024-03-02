% lab 3 ex 2 Normal
p = input("give a param between 0.05≤p≤0.95,p = ")
for n = 1:5:1000
  k = 0:1:n
  resultB = binopdf(k,n,p)
  plot(k,resultB)
  pause(0.5)
endfor
