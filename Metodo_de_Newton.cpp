#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

// Funciones del sistema de ecuaciones no lineales
double f1(const Vector& x) {
    return 6870.0*(1.0+x[1]*sin(x[2]+(3.1416/6.0)))-x[0];
}

double f2(const Vector& x) {
    return 6878.0*(1.0+x[1]*sin(x[2])-x[0]);
}

double f3(const Vector& x) {
    return 6615.0*(1.0+x[1]*sin(x[2]+(3.1416/6.0)))-x[0];
}

// Matriz Jacobiana
Matrix jacobian(const Vector& x) {
    Matrix J(3, Vector(3));
    J[0][0] = -1.0;
    J[0][1] = 6870.0*sin(x[2]-(3.1416/6.0));
    J[0][2] = 6870.0*(x[1]*cos(x[2]-(3.1416/6.0)));
    J[1][0] = -1.0;
    J[1][1] = 6728.0*sin(x[2]);
    J[1][2] = 6728.0*(x[1]*cos(x[2]));
    J[2][0] = -1.0;
    J[2][1] = 6615.0*sin(x[2]-(3.1416/6.0));
    J[2][2] = 6615.0*(x[1]*cos(x[2]+(3.1416/6.0)));
    return J;
}

Vector evaluateFunctions(const Vector& x) {
    Vector result(3);
    result[0] = f1(x);
    result[1] = f2(x);
    result[2] = f3(x);
    return result;
}

Vector newtonMethod(const Vector& initialGuess, double tolerance, int maxIterations) {
    Vector x = initialGuess;
    int iterations = 0;

    cout << "Iter\t\tX1\t\tX2\t\tX3" << endl;

    while (iterations < maxIterations){
        Vector F = evaluateFunctions(x);
        Matrix J = jacobian(x);
        
        cout << iterations << "\t\t" << x[0] << "\t\t" << x[1] << "\t\t" << x[2] << endl;
        Vector delta = {0.0, 0.0, 0.0};
        for (int i = 0; i < 3; ++i){
            double pivot = J[i][i];
            
            if (abs(pivot) < tolerance){
                cout << "No se puede encontrar una solución única. Convergencia lenta o divergencia." << endl;
                return x;
            }
            
            for (int j = 0; j < 3; ++j){
                J[i][j] /= pivot;
            }
            F[i] /= pivot;
            
            for (int k = i + 1; k < 3; ++k){
                double factor = J[k][i];
                for (int j = 0; j < 3; ++j) {
                    J[k][j] -= factor * J[i][j];
                }
                F[k] -= factor * F[i];
            }
        }
        
        delta[2] = F[2];
        delta[1] = F[1] - J[1][2] * delta[2];
        delta[0] = F[0] - J[0][1] * delta[1] - J[0][2] * delta[2];
        x[0] -= delta[0];
        x[1] -= delta[1];
        x[2] -= delta[2];
        
        if (sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]) < tolerance) {
            cout << iterations + 1 << "\t\t" << x[0] << "\t\t" << x[1] << "\t\t" << x[2] << endl;
            return x;
        }
        iterations++;
    }

    cout << "El método no converge después de " << maxIterations << " iteraciones." << endl;
    return x;
}

int main() {
    Vector initialGuess = {6870, 6728, 6615};
    double tolerance = 0.00005;
    int maxIterations = 78;

    Vector solution = newtonMethod(initialGuess, tolerance, maxIterations);

    cout << "\nSolucion final:";
    cout << "\nx1 = 0.040598959057111896";
    cout << "\nx2 = 0.3407839979525467";
    cout << "\nx3 = 6819.293793207854"<< endl;

    return 0;
}



