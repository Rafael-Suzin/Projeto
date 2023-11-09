#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>

using namespace std;

class SystemSolver {
public:
    SystemSolver() {
        introduction();
        input();
        printEquations();
//        system_analize(); // precisa ser refeito, pois para sistema imposiveis retorna respostas, para aqueles com mais de uma resposta retorna uma errada
        solve();
        printSolution();
    }

    SystemSolver(Eigen::MatrixXd& cof,Eigen::VectorXd& igual) {
        this->cof = cof;
        this->igual = igual;
        n_var = cof.cols();
        n_eq = cof.rows();
        var.resize(n_var, " ");
//        char a = 'a'; //'a'=97
        for (int i = 97; (i-97) < n_var; i++) {
            var[i-97] = std::string(1, i);
        }
        introduction();
        printEquations();
        solve();
        printSolution();
    }

    void solve() {
        solution = cof.colPivHouseholderQr().solve(igual);
    }

    Eigen::VectorXd getSolution() {
        return solution;
    }

private:
    Eigen::MatrixXd cof; //matriz nxn// ainda não testei como fica matrizes não quadradas nisso
    Eigen::VectorXd igual;
    Eigen::VectorXd solution;

    int n_var;
    int n_eq;
    vector<string> var;

    void introduction() {
        cout << "System Solver 0.1\n";
        cout << "Resolvendo um sistema linear simples\n";
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
    Eigen::MatrixXd cof(2, 2);
    Eigen::VectorXd igual(2);
    cof << 2, 3, 6, 9;
    igual << 5, 15;   //sistema posivel e indeterminado, solução geral = (x,(5-2x)/3), o programa retorna uma resposta errada

    SystemSolver system2(cof, igual);
    Eigen::VectorXd solution2 = system2.getSolution();

    cout << "Solução do sistema:\n";
    cout << "x = " << solution2(0) << "\n";
    cout << "y = " << solution2(1) << "\n";

    return 0;
}
