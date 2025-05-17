#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>

using namespace std;

complex<double> f(complex<double> x){
    // Aquí debes definir la función que quieres encontrar las raíces
    return 16.0*pow(x,4.0)-(40.0*pow(x,3.0))+(5.0*pow(x,2.0))+(20.0*x)+6.0;
}

void muller(complex<double> x0, complex<double> x1, complex<double> x2, double tol) {
    complex<double> h1 = x1 - x0;
    complex<double> h2 = x2 - x1;
    complex<double> d1 = (f(x1) - f(x0)) / h1;
    complex<double> d2 = (f(x2) - f(x1)) / h2;
    complex<double> d3, a, b, c, rad, den, x3;
    int iter = 1;
    
    cout << setw(9) << "n\t"
         << setw(9) << "x0\t"
         << setw(9) << "x1\t"
         << setw(9) << "x2\t"
         << setw(9) << "x3\t"
         << setw(9) << "f(x3)\t"
         << setw(9) << "Tol" << endl;

    while (true){
        // Calcula los valores de la función en los tres puntos
        a = (d2 - d1) / (h2 + h1);
        b = a*h2 + d2;
        c = f(x2);
        den = sqrt(b*b - 4.0*a*c);
        
        // Encuentra la raíz más cercana a x2
        if (abs(b - den) < abs(b + den)){
            rad = b + den;
        } else {
            rad = b - den;
        }
        x3 = x2 - (2.0*c) / rad;
        
        cout << setw(9) << iter << "\t" 
             << setw(9) << x0 << "\t" 
             << setw(9) << x1 << "\t" 
             << setw(9) << x2 << "\t"
             << setw(9) << x3 << "\t" 
             << setw(9) << f(x3) << "\t"
             << setw(9) << abs(x3 - x2) <<endl;
             
        // Verifica si se ha alcanzado la tolerancia
        if (abs(x3 - x2) < tol){
            cout << "El método ha convergido despues de " << iter << " iteraciones" << endl;
            cout << "La raiz es: " << x3 << endl;
            break;
        }

        // Actualiza los valores para la siguiente iteración
        x0 = x1;
        x1 = x2;
        x2 = x3;
        h1 = x1 - x0;
        h2 = x2 - x1;
        d1 = (f(x1) - f(x0)) / h1;
        d2 = (f(x2) - f(x1)) / h2;
        iter++;
    }
}

int main(){
    complex<double> x0(0.5, 0.0);
    complex<double> x1(-0.5, 0.0);
    complex<double> x2(0.0, 0.0);
    double tol = 1e-5;

    muller(x0, x1, x2, tol);

    return 0;
}