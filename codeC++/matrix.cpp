#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>
#include<Eigen/SparseCholesky>
#include <complex>      // std::complex, std::norm
#include <cmath>
#include <iostream>   // std::cout

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
   // loadMarket(A, "shallow_water1.mtx");
    loadMarket(A, "ex15.mtx");
    int n=A.cols(); 
    Eigen::VectorXd b(n),x(n), xe(n);


    for(int i=0;i<n;i++){
        xe[i]=1;
    }
    // performs a Cholesky factorization of A
    Eigen::SimplicialCholesky<sparsa,Eigen::Upper> chol(A);
    b=A.selfadjointView<Eigen::Upper>() * xe;

    x =chol.solve(b);
    VectorXd diff=x-xe;
    double err=norm(diff)/norm(xe);
    cout<<"errore my norm function"<<endl;
    cout<<err<<endl;
    
    cout<<"errore norm default"<<endl;
    double relative_error = (x-xe).norm()/(xe).norm(); 
    cout << relative_error << endl;
    return 0;
}
