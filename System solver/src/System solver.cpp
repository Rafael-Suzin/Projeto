#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>

using namespace Eigen;
using namespace std;

class SystemSolver {
public:
    SystemSolver() {
        introduction();
        input();
        printEquations();
        system_analize();
//        solve();
        printSolution();
    }

    SystemSolver(MatrixXd& cof,VectorXd& igual) {
        this->cof = cof;
        this->igual = igual;
        n_var = cof.cols();
        n_eq = cof.rows();
        var.resize(n_var, " ");
//        char a = 'a'; //'a'=97
        for (int i = 97; (i-97) < n_var; i++) {
            var[i-97] = string(1, i);
        }
        introduction();
        printEquations();
        system_analize();
//        solve();
        printSolution();
    }

    void solve() {
        solution = cof.colPivHouseholderQr().solve(igual);
    }

    VectorXd getSolution() {
        return solution;
    }

private:
    MatrixXd cof; //matriz nxm
    VectorXd igual;
    VectorXd solution;

    int n_var;
    int n_eq;
    vector<string> var;

    void introduction() {
        cout << "System Solver 0.2\n";
        cout << "Resolvendo um sistema linear\n";
    }

    void input() {
        cout << "Insira o número de variáveis e equações: ";
        cin >> n_var >> n_eq;

        cof.resize(n_eq, n_var);
        igual.resize(n_eq);
        var.resize(n_var);

        for (int i = 0; i < n_var; i++) {
        	cout <<"insira o nome da " <<(i+1)<<"º variavel:\n";
            cin >> var[i];
        }

        for (int i = 0; i < n_eq; i++) {
            for (int j = 0; j < n_var; j++) {
                cout << "Insira o coeficiente da variável " << var[j] << " na equação " << (i + 1) << "º: ";
                cin >> cof(i, j);
            }
            cout << "Insira o valor da igualdade na equação " << (i+1) << ": ";
            cin >> igual(i);
        }
    }
    void system_analize() {
//        cout << "Determinante: " << cof.determinant() << "\n";

        if (n_var == n_eq) {
            if (cof.determinant() != 0) {
                cout << "O sistema é possível e determinado\n";
                solve();
            } else {
                cout << "O sistema pode ser posivel, mas é indeterminado\n";
//                cout << "Solução geral: ";
                // Implementar uma lógica para lidar com sistemas indeterminados
            }
        } else if (n_var > 1 && n_eq == 1) {
            cout << "O sistema possui variáveis livres, mas já está minimizado em apenas uma equação\n";
        } else {
            cout << "O sistema pode ou não ser possível, requer simplificação\n";
            // Implementar lógica para simplificar o sistema se necessário
        }
    }
    void printEquations() {
        cout << "Sistema de Equações:\n";
        for (int i = 0; i < n_eq; i++) {
            cout << "Equação " << (i + 1) << ": ";
            for (int j = 0; j < n_var; j++) {
                cout << cof(i, j) << var[j] << (j == n_var - 1 ? "" : " + ");
            }
            cout << " = " << igual(i) << "\n";
        }
    }

    void printSolution() {
        cout << "Solução do sistema:\n";
        for (int i = 0; i < n_var; i++) {
            cout << "Variável " << var[i] << " = " << solution(i) << "\n";
        }
    }
};

int main() {
    // Caso 1: Chame SystemSolver com entrada do usuário
//    SystemSolver system1;

//     Caso 2: Chame SystemSolver com matriz de coeficientes e vetor de constantes
    MatrixXd cof(2, 2);
    VectorXd igual(2);
    cof <<	2, 3,
    		1, 1;
    igual << 7, 3;   //sistema com solução = (2,1)
    SystemSolver system2(cof, igual);
    VectorXd solution2 = system2.getSolution();

    cout << "Solução do sistema:\n";
    cout << "x = " << solution2(0) << "\n";
    cout << "y = " << solution2(1) << "\n";

    return 0;
}
