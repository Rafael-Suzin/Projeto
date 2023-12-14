// solverinterface.h
#ifndef SOLVERINTERFACE_H
#define SOLVERINTERFACE_H

#include <QVector>
#include <solver.h>
#include <solutionwidget.h>

class SolverInterface {
public:
    SolverInterface(QVector<QVector<double>> matriz, QVector<QString> var, QVector<double> vetor) : var(var) {
        setMatriz(matriz);
        setVetor(vetor);
        solve();
    }

    void setMatriz(QVector<QVector<double>> matriz) {
        matriz_ = convertToEigenMatrix(matriz);
    }

    void setVetor(QVector<double> vetor) {
        vetor_ = convertToEigenVector(vetor);
    }

    void solve() {
        // Chame o solver com as matrizes e vetores configurados
        Solver solver(matriz_, vetor_);
        solution = solver.getSolution(); //VectorXd getSolution()

        // Cria uma instância do SolutionWidget
        SolutionWidget *solutionWidget = new SolutionWidget;

        // Configura os resultados no SolutionWidget
        solutionWidget->setSolution(var, convertToQVector(solution));
        solutionWidget->show();  // Mostre o widget
    }


    QVector<double> convertToQVector(Eigen::VectorXd vetor) {
        int size = vetor.size();
        QVector<double> qVector(size);

        for (int i = 0; i < size; ++i) {
            qVector[i] = vetor(i);
        }

        return qVector;
    }

private:
    Eigen::MatrixXd convertToEigenMatrix(QVector<QVector<double>> matriz) {
        int rows = matriz.size();
        int cols = (rows > 0) ? matriz[0].size() : 0;

        Eigen::MatrixXd eigenMatriz(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                eigenMatriz(i, j) = matriz[i][j];
            }
        }

        return eigenMatriz;
    }

    Eigen::VectorXd convertToEigenVector(QVector<double> vetor) {
        int size = vetor.size();
        Eigen::VectorXd eigenVetor(size);

        for (int i = 0; i < size; ++i) {
            eigenVetor(i) = vetor[i];
        }

        return eigenVetor;
    }

private:
    Eigen::MatrixXd matriz_;
    Eigen::VectorXd vetor_;
    Eigen::VectorXd solution;
    QVector<QString> var;
};

#endif // SOLVERINTERFACE_H
