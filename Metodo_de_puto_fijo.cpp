#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x){
    return pow(x,3) + pow(x,2) - 3*x - 3; // función de iteración
}

double g1(double x){
    return (-3 + pow(x,2) - pow(x,3))/3; // función de iteración g1(x)
}

double g2(double x){
    return sqrt((3 + (3 * x) - pow(x,2))/x); // función de iteración g2(x)
}
double g3(double x){
    return -1 + (((3 * x) + 3)/pow(x,2)); // función de iteración g3(x)
}

double g4(double x){
    return x - ((pow(x,3) + pow(x,2) - (3 * x) - 3)/((3 * pow(x,2)) + (2 * x) - 3)); // función de iteración g4(x)
}

int main(){
    double x0 = 1; // valor inicial
    double error = 0.0001; // tolerancia de error
    int maxIter = 1000; // máximo de iteraciones permitidas
    double x = x0; // valor inicial de x
    
    // Imprime la tabla de iteraciones
    cout << left 
         << setw(10) << "Iter\t" 
         << setw(20) << "g(x)" 
         << setw(20) << "Error" << endl;
    
    for (int i = 0; i < maxIter; i++){
        //double xn = g1(x); // calcula el siguiente valor de x en g1(x)
        //double xn = g2(x); // calcula el siguiente valor de x en g2(x)
        //double xn = g3(x); // calcula el siguiente valor de x en g3(x)
        double xn = g4(x); // calcula el siguiente valor de x en g4(x)
        double err = fabs(xn - x); // calcula el error
        
        cout << left 
             << setw(10) << i 
             << setw(20) << xn
             << setw(20) << err << endl;
        
        if (err < error) { // comprueba el error
            cout << "El método ha convergido despues de " << i << " iteraciones"<< endl;
            cout << "El resultado es: " << xn << endl;
            return 0;
        }
        x = xn; // actualiza el valor de x
    }
    
    cout << "No se ha encontrado una solución adecuada" << endl;
    return 0;
}