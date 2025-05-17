#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Función que se desea encontrar la raíz
double funcion(double x) {
    return pow(x, 3) + 2 * (pow(x, 2)) - 3*(pow(x, 1))-1;
}

// Función que implementa el método de bisección
double biseccion(double a, double b, double tolerancia){
    double c = (a + b) / 2;
    int cont=1;
    cout << setw(5) << "K" 
         << setw(15) << "a" 
         << setw(20) << "b" 
         << setw(20) << "c" //media
         //<< setw(20) << "f(a)"
         //<< setw(20) << "f(b)"
         << setw(20) << "f(c)" 
         << setw(20) << "Tolerancia" //bk+1 - ak+1
         << endl;
    
    while (abs(funcion(c)) > tolerancia){
        cout << setw(5) << cont 
            << setw(20) << setprecision(10) << a 
            << setw(20) << setprecision(10) << b
            << setw(20) << setprecision(10) << c
            //<< setw(20) << setprecision(10) << funcion(a)
            //<< setw(20) << setprecision(10) << funcion(b)
            << setw(20) << setprecision(10) << funcion(c) 
            << setw(20) << setprecision(10) << abs(c-a)
            << endl;
        
        if (funcion(c) == 0.0){
            break;
        } else if (funcion(a) * funcion(c) < 0.0){
            b = c;
        } else {
            a = c;
        }
        c = (a + b) / 2;
        cont++;
  }

    cout << setw(5) << cont 
            << setw(20) << setprecision(10) << a 
            << setw(20) << setprecision(10) << b
            << setw(20) << setprecision(10) << c
            //<< setw(20) << setprecision(10) << funcion(a)
            //<< setw(20) << setprecision(10) << funcion(b)
            << setw(20) << setprecision(10) << funcion(c) 
            << setw(20) << setprecision(10) << abs(c-a)
            << endl;
  
    if (abs(funcion(c)) < tolerancia){
            cout << "El método ha convergido después de " << cont << " iteraciones." << endl;
            return c;
    }
    return c;
}

int main() {
    double a = 1.0; // Extremo izquierdo del intervalo
    double b = 2.0; // Extremo derecho del intervalo
    double tolerancia = 5*pow(10,-3); // Tolerancia para la solución 0.0001
    double raiz = biseccion(a, b, tolerancia);
    cout << "La raíz de la función es: "  << setprecision(10) << raiz << endl;
    return 0;
}



