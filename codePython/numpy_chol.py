import sys
from scipy.io import mmread
import numpy as np
import scipy.linalg 

A = mmread(sys.argv[1])

A=A.toarray()

L = scipy.linalg.cholesky(A,lower=True)

xe=[1]*len(A)

b=np.dot(A,xe)
A_inv = np.linalg.inv(A)
x=np.dot(A_inv,b)

error=scipy.linalg.norm(x-xe)/scipy.linalg.norm(xe)

print(error)
