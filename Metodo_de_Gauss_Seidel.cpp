#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_ITER = 100;
const double TOL = 1e-6;

void imprimirTabla(const vector<vector<double>>& tabla){
    cout << "Iter\t\t";
    for (int i = 0; i < tabla[0].size() - 1; ++i){
        cout << "x" << i + 1 << "\t\t";
    }
    cout << "Error" << endl;

    for (int i = 0; i < tabla.size(); ++i){
        cout << i + 1 << "\t\t";
        for (int j = 0; j < tabla[i].size() - 1; ++j){
            cout << tabla[i][j] << "\t\t";
        }
        cout << tabla[i].back() << endl;
    }
    cout << endl;
}

vector<double> gaussSeidel(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& c){
    int n = A.size();
    vector<double> x = c;
    vector<vector<double>> tabla;

    for (int iter = 0; iter < MAX_ITER; ++iter){
        vector<double> x_ant = x;  
        vector<double> x_act(n, 0.0);  
        
        for (int i = 0; i < n; ++i){
            double sum = 0.0;
            for (int j = 0; j < n; ++j){
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_act[i] = (b[i] - sum) / A[i][i];
        }
        
        x = x_act;
        double error = 0.0;
        for (int i = 0; i < n; ++i){
            error += abs(x[i] - x_ant[i]);
        }
        
        vector<double> fila = x;
        fila.push_back(error);
        tabla.push_back(fila);
        if (error < TOL){
            break;
        }
    }

    imprimirTabla(tabla);
    return x;
}

int main() {
    vector<vector<double>> A = {{2, -1, 0},
                                {-1, 3, -1},
                                {0, -1, 2}}; //coeficientes de las variables en las ecuaciones
    vector<double> b = {1, 8, -5}; //terminos independientes
    vector<double> c = {0, 0, 0}; //aproximacion inicial
   
    vector<double> solucion = gaussSeidel(A, b, c);

    cout << "Solución final:" << endl;
    for (int i = 0; i < solucion.size(); ++i) {
        cout << "x" << i + 1 << " = " << solucion[i] << endl;
    }

    return 0;
}
