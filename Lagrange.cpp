#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
using namespace std;

// Función para calcular el Polinomio de Lagrange e imprimir las iteraciones
double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double xi){
    if (x.size() != y.size()) {
        cout << "Error: Los vectores deben tener la misma longitud." << endl;
        return 0.0;
    }

    double result = 0.0;
    int n = x.size();

    cout << setw(5) << "iter" 
         << setw(15) << "x[i]"
         << setw(15) << "y[i]"
         << setw(15) << "L[i]" 
         << setw(15) << "Error" << endl;

    for (int i = 0; i < n; ++i) {
        double term = y[i];
        
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                term *= (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
        
        cout << setw(5) << i+1
             << setw(15) << x[i] 
             << setw(15) << y[i] 
             << setw(15) << term 
             << setw(15) << abs(y[i] - result) << endl;
    }
    //cout << abs(y[3] - result) << endl;
    return result;
}

// Función para imprimir el Polinomio 
double poli(const vector<double>& x, const vector<double>& y, double xi){
    if (x.size() != y.size()) {
        cout << "Error: Los vectores deben tener la misma longitud." << endl;
        return 0.0;
    }

    double result = 0.0;
    int n = x.size();
    cout << endl;
    cout << setw(5) << "Polinomio: " ;
    
    for (int i = 0; i < n; ++i) {
        double term = y[i];
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                term *= (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
        
        cout << setw(5) << term*y[i] << "x^" << i << " + ";
    }
    return result;
}

int main() {
    vector<double> x = {1.3, 1.6, 1.9}; // Valores de x conocidos
    vector<double> y = {0.6200860, 0.4554022, 0.2818186}; // Valores de y conocidos
    double xi = 1.5; // Valor objetivo para interpolar
    double interpolatedValue = lagrangeInterpolation(x, y, xi);
    double p = poli(x, y, xi);
    
    cout << endl;
    cout << endl;
    cout << "El valor interpolado en x = " << xi << " es y = " << interpolatedValue << endl;
    return 0;
}