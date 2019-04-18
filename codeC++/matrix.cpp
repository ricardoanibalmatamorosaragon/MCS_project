#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>
#include<Eigen/SparseCholesky>
#include <iostream>   // std::cout

typedef Eigen::SparseMatrix<double, Eigen::ColMajor> sparsa;
using namespace Eigen;
using namespace std;

int main(int argc, char** argv){
    sparsa A; 
   // loadMarket(A, "shallow_water1.mtx");
    loadMarket(A, "ex15.mtx");
    int n=A.cols(); 
    Eigen::VectorXd b(n),x(n), xe(n);


    for(int i=0;i<n;i++){
        xe[i]=1;
    }
    // performs a Cholesky factorization of A
    Eigen::SimplicialCholesky<sparsa,Eigen::Lower> chol(A);
    b=A.selfadjointView<Eigen::Lower>() * xe;

    x =chol.solve(b);
    double relative_error = (x-xe).norm()/(xe).norm(); 
    cout << relative_error << endl;
    return 0;
}
