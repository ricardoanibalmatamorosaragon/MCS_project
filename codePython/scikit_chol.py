import sys
from scipy.io import mmread
import numpy as np
from sksparse.cholmod import cholesky

A = mmread(sys.argv[1]).tocsc()

factor = cholesky(A)

xe=[1]*A.shape[0]

b=A.dot(xe)

x =factor(b)


error=np.linalg.norm(x-xe)/np.linalg.norm(xe)

print(error)
