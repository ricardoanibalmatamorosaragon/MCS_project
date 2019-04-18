#include <Eigen/Sparse>
#include <algorithm>
#include <unsupported/Eigen/SparseExtra>
#include<Eigen/SparseCholesky>
#include <numeric>
#include <vector>
#include <complex>      // std::complex, std::norm
#include <cmath>
#include <iostream>   // std::cout
#include <string>     // std::string, std::stof
typedef Eigen::SparseMatrix<double, Eigen::ColMajor> sparsa;
using namespace Eigen;
using namespace std;

double norm(VectorXd & vector){
    double temp=0;
    //cout<<vector.size()<<endl;
    for(int i=0;i<vector.size();i++){
        std::complex<double> mycomplex(vector[i],vector[i]);
        temp+=std::norm(mycomplex);
    }
    return temp;
}

int main(int argc, char** argv){
    sparsa A; 
    loadMarket(A, "shallow_water1.mtx");
    int n=A.cols(); 
    Eigen::VectorXd b(n),x(n), xe(n);


    for(int i=0;i<n;i++){
        xe[i]=1;
    }
    // performs a Cholesky factorization of A
    Eigen::SimplicialCholesky<sparsa> chol(A);
    b=A*xe;

    x =chol.solve(b);
    Eigen::VectorXd diff=x-xe;
    double err=norm(diff)/norm(xe);
    cout<<err<<endl;
    return 0;
}
