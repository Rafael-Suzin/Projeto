#ifndef SOLVER_H
#define SOLVER_H

#include <QCoreApplication>
#include <iostream>
#include <D:\Downloads\Projeto\Projeto\Eigen\Dense>
#include <vector>
#include <string>

using namespace Eigen;
using namespace std;

class Solver {
public:
    Solver(MatrixXd cof, VectorXd igual) {
        this->cof = cof;
        this->igual = igual;
        n_var = cof.cols();
        n_eq = cof.rows();
        retorno = system_analize();
    }

    void solve() {
        solution = cof.colPivHouseholderQr().solve(igual);
    }

    VectorXd getSolution() {
        return solution;
    }

    double det() {
        return cof.determinant();
    }

    int returno() {
        return retorno;
    }

    int get_n_var() {
        return n_var;
    }

    int get_n_eq() {
        return n_eq;
    }

private:
    MatrixXd cof; // matriz nxm
    VectorXd igual;
    VectorXd solution;

    int n_var;
    int n_eq;
    int retorno;

    int system_analize() {
        if (n_var == n_eq) {
            if (cof.determinant() != 0) {
                solve();
                return 0;
            } else {
                return 2;
            }
        } else if (n_var > 1 && n_eq == 1) {
            return 1;
        } else {
            return -1;
        }
    }
};



#endif // SOLVER_H
