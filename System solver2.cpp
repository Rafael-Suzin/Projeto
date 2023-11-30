#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <string>

using namespace Eigen;
using namespace std;

class SystemSolver {
public:
    SystemSolver(MatrixXd cof,VectorXd igual) {
        this->cof = cof;
        this->igual = igual;
        n_var = cof.cols();
        n_eq = cof.rows();
        var.resize(n_var, " ");
//        char a = 'a'; //'a'=97
        for (int i = 0; i < n_var; i++) {
            var[i] = string(1, i+'a');
        }
        retorno=system_analize();
    }

    void solve() {
        solution = cof.colPivHouseholderQr().solve(igual);
    }

    VectorXd getSolution() {
        return solution;
    }
    double det(){
    	return cof.determinant();
    }
    int returno(){
    	return retorno;
    }
    int get_n_var(){
    	return retorno;
    }
    int get_n_eq(){
    	return n_eq;
    }
private:
    MatrixXd cof; //matriz nxm
    VectorXd igual;
    VectorXd solution;

    int n_var;
    int n_eq;
    vector<string> var;
    int retorno;
    int system_analize() {
//        cout << "Determinante: " << cof.determinant() << "\n";

        if (n_var == n_eq) {
            if (cof.determinant() != 0) {
                solve();
                return 0;
            } else {
//                cout << "Solução geral: ";
                // Implementar uma lógica para lidar com sistemas indeterminados
                return 2;
            }
        } else if (n_var > 1 && n_eq == 1) {
        	return 1;
        } else {

            // Implementar lógica para simplificar o
            return -1;
        }
    }
};

class SystemSolverInterfaceCmd {
	SystemSolver systemSolver;
    MatrixXd cof; //matriz nxm
    VectorXd igual;

    vector<string> var;

public:
	SystemSolverInterfaceCmd(){
        introduction();
        input();
        systemSolver(&cof,&igual);
        system_analize(systemSolver.returno());
        printSolution(systemSolver.getSolution());
    }
//	SystemSolverInterfaceCmd(MatrixXd& cof,VectorXd& igual) {
//		SystemSolver(cof,igual);
//    }


    VectorXd getSolution() {
        return systemSolver.getSolution();
    }
private:
    void introduction() {
        cout << "System Solver 0.5\n";
        cout << "Resolvendo um sistema linear\n";
    }

    void input() {
        int n_var;
        int n_eq;
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
        printEquations(n_eq,n_var);
    }
    void system_analize(int a) {
//        cout << "Determinante: " << cof.determinant() << "\n";
        switch (a) {
            case 0:
            	cout << "O sistema é possível e determinado\n";
            	break;
            case 2:
            	cout << "O sistema pode ser posivel, mas é indeterminado\n";
            	break;
			case 1:
				cout << "O sistema possui variáveis livres, mas já está minimizado em apenas uma equação\n";
				break;
            case -1:
            	cout << "O sistema pode ou não ser possível, requer simplificação\n";
            	break;
            default:
            	cout << "Erro desconhecido\n";
                break;
        }
    }

    void printEquations(int n_eq,int n_var) {
        cout << "Sistema de Equações:\n";
        for (int i = 0; i < n_eq; i++) {
            cout << "Equação " << (i + 1) << ": ";
            for (int j = 0; j < n_var; j++) {
                cout << cof(i, j) << var[j] << (j == n_var - 1 ? "" : " + ");
            }
            cout << " = " << igual(i) << "\n";
        }
    }

    void printSolution(VectorXd solution) {
        cout << "Solução do sistema:\n";
        for (int i = 0; i < solution.size(); i++) {
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
