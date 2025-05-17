#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Función para calcular las diferencias divididas
double DD(const vector<double>& x, const vector<double>& y, int inicio, int fin){
    if (inicio == fin){
        return y[inicio];
    }
    else{
        return (DD(x, y, inicio + 1, fin) - DD(x, y, inicio, fin - 1)) / (x[fin] - x[inicio]);
    }
}

// Función para calcular las diferencias divididas hacia adelante
vector<double> DDAdelante(const vector<double>& x, const vector<double>& y){
    int n = x.size();
    vector<double> divididas(n);
    divididas[0] = y[0];
    
    for (int i = 1; i < n; i++){
        divididas[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
    }
    
    return divididas;
}

// Función para calcular las diferencias divididas hacia atrás
vector<double> DDAtras(const vector<double>& x, const vector<double>& y){
    int n = x.size();
    vector<double> divididas(n);
    divididas[n - 1] = y[n - 1];
    
    for (int i = n - 2; i >= 0; i--){
        divididas[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    }
    
    return divididas;
}

// Función para calcular las diferencias divididas centradas
vector<double> DDCentradas(const vector<double>& x, const vector<double>& y){
    int n = x.size();
    vector<double> divididas(n);
    vector<double> divididasAdelante = DDAdelante(x, y);
    vector<double> divididasAtras = DDAtras(x, y);
    
    for (int i = 0; i < n; i++){
        divididas[i] = (divididasAdelante[i] + divididasAtras[i]) / 2.0;
    }
    
    return divididas;
}

// Función para realizar la interpolación de Lagrange
double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double xi){
    if (x.size() != y.size()){
        cout << "Error: Los vectores deben tener la misma longitud." << endl;
        return 0.0;
    }
    double result = 0.0;
    int n = x.size();
    
    //Para difrencia hacia delante, atras y centradas
    //vector<double> diferenciasDivididas = DDCentradas(x, y);
    //vector<double> diferenciasDivididas = DDAdelante(x, y);
    //vector<double> diferenciasDivididas = DDAtras(x, y);

    for (int i = 0; i < n; i++){
        //double term = diferenciasDivididas[i];  //Para difrencia hacia delante, atras y centradas
        double term = DD(x, y, 0, i); //Para difrencia dividida general
        
        for (int j = 0; j < i; j++){
            term *= (xi - x[j]);
        }
        result += term;
    }

    return result;
}

int main(){
    // Datos de ejemplo
    vector<double> x = {1.0, 1.3, 1.6, 1.9, 2.2};
    vector<double> y = {0.7651977, 0.6200860, 0.4554022, 0.2818186, 0.1103623};
    double xi = 2.0; // Valor a interpolar
    double result = lagrangeInterpolation(x, y, xi); // Realiza interpolación de Lagrange
    
    // Imprime las diferencias divididas 
    int n = x.size();
    cout << setw(5) << "x";
    for (int i = 0; i < n; i++) {
        cout << setw(11) << i << " DD";
    }
    cout << endl;

    //Para difrencia hacia delante, atras y centradas
    //vector<double> diferenciasDivididas = DDCentradas(x, y);
    //vector<double> diferenciasDivididas = DDAdelante(x, y);
    //vector<double> diferenciasDivididas = DDAtras(x, y);
    
    for (int i = 0; i < n; i++) {
        cout << setw(5) << x[i];
        for (int j = i; j < n; j++) {
            //cout << setw(15) << diferenciasDivididas[i]; //Para difrencia hacia delante, atras y centradas
            cout << setw(15) << DD(x, y, i, j); //Para difrencia dividida general
        }
        cout << endl;
    }

    cout << endl;
    cout << "El resultado de la interpolación de Lagrange en " << xi << " es: " << result << endl;

    return 0;
}
