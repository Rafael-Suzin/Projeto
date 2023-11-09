//v0.003
// Created on: Sep 26, 2023
//     Author: Rafael
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class System_Solver {

    vector<char> var;
    vector<int> cof; //com erro era para ser uma matriz
//   vector<vector<int>> matriz(linhas,vector<int>(colunas));
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
    	cout <<"system solver 0.003v \n";
    	cout <<"sistema linear simples\n";
    }
    void dados(){
    	cout <<"insira quantas variaveis e quantas equações\n";
    	cin >>n_var>>n_eq;
    	resize();

		for (int i = 0; i < n_var; i++) {
			cout <<"insira o nome da sua " <<(i+1)<<"º variavel\n";
			cin >> var[i];
		}
    	for (int i = 0;  i< n_eq; i++) {
			for (int j = 0; j < n_var; ++j) {

				cout <<"insira o coefiente da variavel "<<var[j]<<"\n";
				cin >> cof[j];
			}
			cout <<"insira a igualdade\n";
			cin >> igual[i];
		}
    }
    void imprime_exp(){
		for (int i = 0;  i< n_eq; i++) {
			for (int j = 0; j < n_var; ++j) {
				cout <<cof[j]<<var[j];
				if(i+1<n_eq){
					cout<<"+";
				}
			}
			cout<<"="<<igual[i]<<"\n";
		}
    }
    void solve(){
    	value[0]=igual[0]/cof[0];
    	imprime_val();
    }
    void imprime_val(){
    	cout <<"sistema resolvido:\n";
    	cout <<var[0]<<"="<<value[0]<<"\n";
    }
    void resize(){
    	var.resize(n_var);
		cof.resize(n_var);
		igual.resize(n_eq);
		value.resize(n_var);
    }
    void system_analize(){

    	if (n_var==(n_eq==1)){
			cout <<"sistema é simples\n";
			solve();

    	}
    	else if(n_var==n_eq){ //det!=0
			cout <<"o sistema é posivel e determinado\n";
			//solve_cramer
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

