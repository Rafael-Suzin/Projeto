/*
 * complex.c
 *
 *  Created on: Oct 15, 2023
 *      Author: Rafael
 */
#include <iostream>
#include <cmath>

using namespace std;

class Complex {
    double x;
    double y;
    double modulo;
    double arco;



    double Modulo_() {
    	modulo=sqrt(x * x + y * y);
        return modulo;
    }
    double Arco_() {
    	arco=atan2(y,x)*sinal(y);
        return arco;
    }
    double sinal(double y){
    	if(y>=0)
    		return 1;
    	else{
    		return -1;
    	}
    }
public:
    double real(){return x;}
    double imaginario(){return y;}
    double Modulo(){return modulo;}
    double Arco(){return arco;}
    Complex() : modulo(0), arco(0),x(0),y(0) {
//    	x=modulo*cos(arco);
//    	y=modulo*sin(arco);
    }
    Complex(double x, double y) : x(x), y(y) {
    	Modulo_();
    	Arco_();
    }

//    Complex(double modulo, double arco) : modulo(modulo), arco(arco) {
//    	x=modulo*cos(arco);
//    	y=modulo*sin(arco);
//    }
    Complex operator=(Complex outro) {
        x = outro.x;
        y = outro.y;
        modulo = outro.modulo;
        arco = outro.arco;
        return *this;
    }
    Complex operator+(Complex& outro){
        return Complex(this->x+outro.x, this->y*outro.y);
    }
    Complex operator-() {
        return Complex(-x, -y);
    }
//    Complex operator*( Complex& outro){ //multiplicação polar
//    	Complex result;
//        result.modulo = this->modulo * outro.modulo;
//        result.arco = this->arco + outro.arco;
//        result.x=result.modulo*cos(arco);
//        result.y=result.modulo*sin(arco);
//        return result;
//    }
    Complex operator*(Complex outro){ //multiplicação algebrica
        return Complex(this->x*outro.x - this->y * outro.y, this->x*outro.y + this->y * outro.x);
    }
    Complex operator*(double num){ //multiplicação algebrica
    	return Complex(x*num, y*num);
    }
    Complex operator/(double num){ //multiplicação algebrica
        return Complex(x/num, y/num);
    }
    Complex operator~() {
        return Complex(x, -y);
    }
    Complex operator!(){ //"inversão", faz o inverso multiplicativo
        return ~(*this)/(x*x+y*y);
    }
    Complex operator/(Complex outro){// Divisão usando o inverso multiplicativo
        return (*this)*(!outro);
    }

    friend ostream &operator<<(ostream &output, Complex &outro){
    	if(outro.x==0){
    		output << outro.y<<"i";
    	}
    	else if(outro.y<0){
    		output << outro.x << "" << outro.y<<"i";
    	}
    	else if(outro.y>0){
    		output << outro.x << "+" << outro.y<<"i";
    	}
    	else{
        output << outro.x;
    	}
        return output;
    }

    void ComplexAlgebric(){
    	if(x==0)
    		cout << y << "i";
    	else if(y<0){
    		cout << x<< ""<< y << "i";
    	}
    	else if(y>0)
    		cout << x<< "+"<< y << "i";
    	else{
    		cout << x;
    	}
    }
    void ComplexPolar(){
		cout << modulo<< "<"<< arco;
    }
};
int main() {
    Complex n1(1, 1);
    Complex n2(0, 2);
    Complex n3=(-n1);
    Complex n4=(~n3);
//    n3.ComplexAlgebric();
    cout << n1<<"\n";
    cout << n3<<"\n";
    cout << n4<<"\n";
//    cout << "\n";
//    n3.ComplexPolar(); //arco em radianos
    cout << "\n";
//    n4.ComplexPolar(); //arco em radianos

    return 0;
}





