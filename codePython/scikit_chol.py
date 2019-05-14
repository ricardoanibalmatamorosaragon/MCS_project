import sys
from scipy.io import mmread
import numpy as np
from sksparse.cholmod import cholesky
from datetime import datetime 
from memory_control import measure_memory_usage 

#path linux 
path = "./mtxMatrix/"

matrix_list= ["ex15.mtx", "shallow_water1.mtx", "cfd1.mtx" , "cfd2.mtx" , "apache2.mtx" , "parabolic_fem.mtx" , "G3_circuit.mtx"]
#matrix_list= ["ex15.mtx"]

def memory_usage_psutil():
    # return the memory usage in MB
    import psutil
    import os
    process = psutil.Process(os.getpid())
    mem = process.memory_info().rss / float(1024.0**2)
    return mem

def chol(A):
    factor = cholesky(A)
    xe=[1]*A.shape[0]
    b=A.dot(xe)
    x =factor(b)
    error=np.linalg.norm(x-xe)/np.linalg.norm(xe)
    f.write("Error: "+str(error)+"\n")

#path linux
f = open("./codePython/resultsW.txt","w+") 

for matrix in matrix_list:
    f.write("matrix: "+matrix+"\n")
    read_in=datetime.now()
    A = mmread(path+matrix).tocsc()
    read_end=datetime.now() - read_in
    f.write("size matrix : "+str(A.shape[0])+"x"+str(A.shape[1])+"\n")
    f.write("time for matrix read: "+str(read_end)+"\n")
    start_chol=datetime.now()
   # mem = measure_memory_usage(chol(A),"", memory_denominator=1024.0**2, memory_usage_refresh=0.005)
    chol(A)
    end_chol=datetime.now() - start_chol
    f.write("time for solve system with chol: "+str(end_chol)+"\n")
    f.write("memory used to solve system with chol: "+str(memory_usage_psutil())+" MB \n")
    #print(memory_usage_psutil())
    f.write("\n")
f.close()
