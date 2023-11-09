//v0.005
#include <iostream>
#include <vector>

using namespace std;

class Matriz {
public:
    vector<vector<int>> matriz;
    int det=0;
    bool det_is_set=false;

    Matriz() {
    	det=0;
    }
    Matriz(vector<vector<int>> m) {
    	resize_m(m.size(),m[0].size());
		matriz = m;
		determinante();
    }
    Matriz(int linhas, int colunas) {
    	resize_m(linhas,colunas);
    	preencherMatriz();
		determinante();
    }

    void preencherMatriz() {
        for (unsigned int i = 0; i < matriz.size(); i++) {
            for (unsigned int j = 0; j < matriz[i].size(); j++) {
                cout << "Digite o valor para a posição [" << i << "][" << j << "]: ";
                cin >> matriz[i][j];
            }
        }
    }
    void imprimirMatriz() {
        for (unsigned int i = 0; i < matriz.size(); i++) {
            for (unsigned int j = 0; j < matriz[i].size(); j++) {
                cout << matriz[i][j] << " ";
            }
            cout << endl;
        }
    }
	int size(){
		return sizeof(matriz)/sizeof(matriz[0][0]);
	}
	void resize_m(int lin,int col){
		matriz.resize(lin, vector<int>(col));
	}
	int determinante(){
		if (matriz.size() == 2 && matriz[0].size() == 2){
			det=(matriz[0][0]*matriz[1][1]-matriz[0][1]*matriz[1][0]);
			det_is_set=true;
		}
		if(matriz.size() == 1 && matriz[0].size() == 1){
			det=(matriz[0][0]);
			det_is_set=true;
		}
		return det;
	}
	bool det_set(){return det_is_set;};
	int get_det(){
		if(det_is_set){
			return det;
		}
		cout<<"det not set";
		return 0;
	}
    vector<vector<int>> getMatriz() {
        return matriz;
    }
};

class System_Solver {

    vector<char> var;
    Matriz cof;
    vector<int> igual;
    vector<int> value;


    int n_var;
    int n_eq;

    void incio(){
    	introduction();
    	dados();
    	imprime_exp();
    	system_analize();
//    	solve();
//    	imprime_val();

    }
    void introduction(){
    	cout <<"system solver 0.005v \n";
    	cout <<"sistema linear simples\n";
    }
    void dados(){
    	cout <<"insira quantas variaveis e quantas equaçoes \n";
    	cin >>n_var>>n_eq;
    	resize();

		for (int i = 0; i < n_var; i++) {
			cout <<"insira o nome da sua " <<(i+1)<<"º variavel\n";
			cin >> var[i];
		}
    	for (int i = 0;  i< n_eq; i++) {
			for (int j = 0; j < n_var; ++j) {

				cout <<"insira o coefiente da variavel "<<var[j]<<"\n";
				cin >> cof.matriz[i][j];
			}
			cout <<"insira a igualdade\n";
			cin >> igual[i];
		}
//    	cout <<cof.size();
    }
    void imprime_exp(){
		for (int i = 0;  i< n_eq; i++) {
			for (int j = 0; j < n_var; ++j) {
				cout <<cof.matriz[i][j]<<var[j];
				if(j+1<n_eq){
					cout<<"+";
				}
			}
			cout<<"="<<igual[i]<<"\n";
		}
    }
    void solve(){
//    	value[0]=igual[0]/cof[0];
    	imprime_val();
    }
    void imprime_val(){
    	cout <<"sistema resolvido:\n";
    	cout <<var[0]<<"="<<value[0]<<"\n";
    }
    void resize(){
//    	cout<<"aumentando o vetor das variaveis \n";
    	var.resize(n_var);
//    	cout<<"aumentando a matriz de coficientes \n";
    	cof.resize_m(n_eq,n_var);
		igual.resize(n_eq);
		value.resize(n_var);
    }
    void system_analize(){
    	cof.determinante();
    	if (n_var<=2){
			cout <<"determinate ="<<cof.det<<"\n";
    	}
    	if (n_var==(n_eq==1)){
			cout <<"sistema simples\n";
			solve();

    	}
    	else if(n_var==n_eq&&cof.det!=0){ //det!=0
			cout <<"o sistema posivel e determinado\n";
			//solve_cramer ou matriz inversa
    	}
    	else if(n_var>1&&n_eq==1){
			cout <<"o sistema possui variaveis livres, mas já está minimizado em apenas uma equação\n";
//    		Solver_mat.isolar(var[1]);
		}
    	else { //(en_eq)
			cout <<"o sistema pode ou não ser possivel, requer simplificação\n";
//    		Solver_mat.simplificar?
		}
    }
public:
    System_Solver(){
    	incio();
    }
};

int main() {


	System_Solver();

    return 0;
}


