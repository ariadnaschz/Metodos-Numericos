#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_ITER = 100;
const double TOL = 0.01; //tolerancia

void jacobiMethod(double A[][3], double b[], int n, double c[]) {
    double x[n];
    double x_prev[n];
    int iter = 0;
    double error = 0.0;

    for (int i = 0; i < n; i++) {
        x[i] = c[i]; 
    }

    cout << "Iter\t\t";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << "\t\t";
    }
    cout << "Error\n";

    do {
        iter++;
        error = 0.0;
        
        for (int i = 0; i < n; i++) {
            x_prev[i] = x[i];
            
            double sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x_prev[j];
                }
            }
            
            x[i] = (b[i] - sum) / A[i][i];
            error += abs(x[i] - x_prev[i]);
        }
        
        cout << iter << "\t\t";
        for (int i = 0; i < n; i++) {
            cout << fixed << setprecision(6) << x[i] << "\t";
        }
        cout << error << "\n";
    } while (error > TOL && iter < MAX_ITER);

    cout << "\nSolución:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << x[i] << "\n";
    }
}

int main() {
    double A[][3] = {{2, -1, 0},
                     {-1, 3, -1},
                     {0, -1, 2}}; //coeficientes de las variables en las ecuaciones
    double b[] = {1, 8, -5}; //terminos independientes
    double c[] = {0, 0, 0}; //aproximacion inicial
    int n = sizeof(b) / sizeof(b[0]);

    jacobiMethod(A, b, n, c);
    return 0;
}
