//v0.001
// Created on: Sep 26, 2023
//     Author: Rafael
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;

class System_Solver {


    char var;
    int cof;
    int igual;
    int value;

    void incio(){
    	introduction();
    	dados();
    	imprime_exp();
    	solve();
    	imprime_val();

    }
    void introduction(){
    	cout <<"system solver 0.0001v \n";
    	cout <<"sistema linear de uma variavel\n";
    }
    void dados(){
    	cout <<"insira o nome da sua primeria variavel\n";
    	cin >> var;
    	cout <<"insira o coefiente da variavel\n";
    	cin >> cof;
    	cout <<"insira a igualdade\n";
    	cin >> igual;
    }
    void imprime_exp(){
    	cout <<cof<<var<<"="<<igual<<"\n";
    }
    void solve(){
    	value=igual/cof;
    }
    void imprime_val(){
    	cout <<"sistema resolvido:\n";
    	cout <<var<<"="<<value<<"\n";
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
