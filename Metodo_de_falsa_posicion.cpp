#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x){
    // Aquí se define la función a utilizar
    return x - cos(x);
}

double falsa_posicion(double a, double b, double tol, int nmax){
    double fa = f(a);
    double fb = f(b);
    int n = 0;
    double c, cAnt;
    cout << setw(9) << "K\t"
         << setw(9) << "a\t"
         << setw(9) << "b\t"
         << setw(9) << "Pn\t" //Aproximacion
         << setw(9) << "f(Pn)\t"
         << setw(9) << "Tolerancia" << endl; //Pn-a
    
    while (n < nmax){
        cAnt=c;
        c = (a*fb - b*fa)/(fb - fa);
        double fc = f(c);
        cout << setw(9) << n+1 << "\t" 
             << setw(9) << a << "\t" 
             << setw(9) << b << "\t" 
             << setw(9) << c << "\t" 
             << setw(9) << f(c) << "\t"
             << setw(9) << abs(c-cAnt) <<endl;
             
        if (abs(fc) < tol) {
            cout << "El método de falsa posición ha convergido después de " << n+1 << " iteraciones." << endl;
            return c;
        }
        if (fa*fc < 0){
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        n++;
    }
    cout << "El método de falsa posición no ha convergido después de " << nmax << " iteraciones." << endl;
    return c;
}

int main(){
    double a = 0.5; // Extremo izquierdo del intervalo
    double b = 1.0; // Extremo derecho del intervalo
    double tol = 5*pow(10,-5); //tolerancia (en el exponente tine que ser el que de la profa+1 "si es -4, entonces ponemos -5")
    int nmax = 1000; //maximo numero de interaciones (nos ayudara a saber cuantas interaciones despues convergio)
    double raiz = falsa_posicion(a,b,tol,nmax);
    cout << "La raiz de la función es: " << raiz << endl;
    return 0;
}