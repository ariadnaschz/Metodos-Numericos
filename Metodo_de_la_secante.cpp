#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x) {  // definición de la función f(x)
    return x - cos(x); 
}

double secante(double x0, double x1, double tolerancia){
    double xn, fx0, fx1, fxn, error;
    fx0 = f(x0);
    fx1 = f(x1);
    
    cout << setw(5) << "K" 
         << setw(20) << "x0" 
         << setw(20) << "x1" 
         << setw(20) << "xn" 
         << setw(20) << "f(xn)" 
         << setw(20) << "Tolerancia" //x1 - x0
         << endl;
    
    for(int i = 0; i < 1000; i++){
        xn = x1 - ((fx1*(x1 - x0))/(fx1 - fx0)); // fórmula del método de la secante
        fxn = f(xn);
        error = abs(x1-x0); //abs((xn - x1) / xn); // calculando el error relativo
        cout << setw(5) << i+1 
             << setw(20) << x0 
             << setw(20) << x1 
             << setw(20) << xn 
             << setw(20) << f(xn) 
             << setw(20) << error 
             << endl;
        
        if(error < tolerancia) { // si el error es menor que la tolerancia, se detiene la iteración
            cout << "El método ha convergido después de " << i+1 << " iteraciones." << endl;
            return xn;
        }
        
        // actualizando los valores para la siguiente iteración
        x0 = x1;
        fx0 = fx1;
        x1 = xn;
        fx1 = fxn;
    }
    return xn; // retorna la aproximación de la raíz
}

int main(){
    double x0 = 0.5; // Extremo izquierdo del intervalo
    double x1 = 1.0; // Extremo derecho del intervalo
    double tolerancia = 5*pow(10,-4); // tolerancia
    double raiz = secante(x0, x1, tolerancia);
    cout << "La raíz aproximada es: " << raiz << endl;
    
    return 0;
}