import numpy as np
import matplotlib.pyplot as plt

def func(a,b,c,d,arg,x0):
    return a+b*(arg-x0)+c*(arg-x0)**2+d*(arg-x0)**3

a=np.loadtxt('coef.txt')
x=np.loadtxt('x.txt')

for i in range(11):
    plt.plot(np.linspace(x[i][0],x[i+1][0],100),func(a[i][0],a[i][1],a[i][2],a[i][3],np.linspace(x[i][0],x[i+1][0],100),x[i][0]), 'g')
   
plt.plot(x[:,0],x[:,1],'ro')
plt.grid()
plt.show()
