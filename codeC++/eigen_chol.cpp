#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>
#include<Eigen/SparseCholesky>
#include <iostream>   // std::cout
#include<string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <stack>

typedef Eigen::SparseMatrix<double, Eigen::ColMajor> sparsa;
using namespace Eigen;
using namespace std;


std::stack<clock_t> tictoc_stack;

void tic() {
    tictoc_stack.push(clock());
}

double toc() {
    double time =((double)(clock() - tictoc_stack.top())) / CLOCKS_PER_SEC;
    tictoc_stack.pop();
    return time;
}

int main(int argc, char** argv){
    ofstream myfile;
    
    //file to save results
    myfile.open ("/home/ricardo/Scrivania/codiceC/results.txt");

    //input matrix
    //string matrix_list[]={"ex15.mtx", "shallow_water1.mtx", "cfd1.mtx" , "cfd2.mtx" , "apache2.mtx" , "parabolic_fem.mtx" , "G3_circuit.mtx"};
    string matrix_list[]={"ex15.mtx", "shallow_water1.mtx"};
    string path="/home/ricardo/Scrivania/codiceC/mtx/";
    
    //matrix format to eigen    
    sparsa A; 
    int n = std::end(matrix_list) - std::begin(matrix_list);
    for(int i=0; i<n;i++){
        tic();
        //open matrix 
        loadMarket(A, path+matrix_list[i]);

        //save time load matrix
        double final_read = toc();
        myfile << "matrix : "+matrix_list[i]+"\n";
        int n=A.cols(); 
        myfile << "size matrix : "+to_string(n)+"x"+to_string(n)+"\n";
        Eigen::VectorXd b(n),x(n), xe(n);
        ostringstream strs_read;
        strs_read << final_read;
        myfile << "time for matrix read : "+strs_read.str()+"\n";
        xe=VectorXd::Constant(A.rows(), 1);

        // performs a Cholesky factorization of A
        tic();
        Eigen::SimplicialCholesky<sparsa,Eigen::Lower> chol(A);
        b=A.selfadjointView<Eigen::Lower>() * xe;
        x =chol.solve(b);

        //save time to solve problem with chol
        double final_chol=toc();
        ostringstream strs_chol;
        strs_chol << final_chol;
        myfile << "time for solve system with chol : "+strs_chol.str()+"\n";

        //calculate relative error
        double relative_error = (x-xe).norm()/(xe).norm(); 
        ostringstream strs;
        strs << relative_error;

        myfile <<"error : "+strs.str()+"\n";
        myfile <<"\n";
    }
    myfile.close();
    return 0;
}
