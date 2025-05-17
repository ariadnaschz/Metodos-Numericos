#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

void cubicSplineInterpolation(const vector<double>& x, const vector<double>& y, int n, vector<double>& a, vector<double>& b, vector<double>& c, vector<double>& d) {
    // Calcular las diferencias de x y y
    vector<double> h(n), alpha(n), l(n + 1), mu(n + 1), z(n + 1);
    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
        alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // Resolver el sistema tridiagonal
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;
    for (int i = 1; i < n; ++i) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;
    c.resize(n + 1);
    b.resize(n);
    d.resize(n);
    c[n] = 0.0;

    // Resolver para los coeficientes c, b y d
    for (int j = n - 1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    a = y;
}

double interpolateSpline(const vector<double>& x, const vector<double>& y, const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d, double xi) {
    int n = x.size();
    int k = 0;
    for (int i = 1; i < n; ++i) {
        if (xi <= x[i]) {
            k = i - 1;
            break;
        }
    }

    double dx = xi - x[k];
    double value = a[k] + b[k] * dx + c[k] * dx * dx + d[k] * dx * dx * dx;
    return value;
}

void printTable(const vector<double>& x, const vector<double>& y, const vector<double>& a, const vector<double>& b, const vector<double>& c, const vector<double>& d) {
    int n = x.size();
    cout << "Tabla de coeficientes del spline cúbico:" << endl;
    cout << setw(5) << "i" 
             << setw(15) << "x[i]" 
             << setw(15) << "a[i]" 
             << setw(15) << "b[i]" 
             << setw(15) << "c[i]" 
             << setw(15) << "d[i]" << endl;

    for (int i = 0; i < n; ++i) {
        cout << setw(5) << i+1 
             << setw(15) << x[i] 
             << setw(15) << a[i] 
             << setw(15) << b[i] 
             << setw(15) << c[i] 
             << setw(15) << d[i] << endl;
    }
    
    cout << endl;
    cout << setw(5) << "Polinomios" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(5) << "S(" << i+1 << ")= ";
        cout << a[i] << " + " << b[i] << "(x - " << x[i] << ") + " << c[i] << "(x - " << x[i] << ")^2 + " << d[i] << "(x - " << x[i] << ")^3" << endl;
    }
}

int main() {
    vector<double> x = {0.0, 0.25, 0.4, 0.6};
    vector<double> y = {0.0, 0.21106, 0.39983, 0.40528};
    int n = x.size() - 1;

    /*
    // Condiciones de frontera fija
    vector<double> a_fixed = {0.1, 3.58502082};  // Frontera izquierda fija
    vector<double> b_fixed = {0.4, 2.16529366};  // Frontera derecha fija
    */
    
    // Agregar los coeficientes calculados por el spline cúbico
    vector<double> a, b, c, d;
    cubicSplineInterpolation(x, y, n, a, b, c, d);

    /*
    // Agregar las condiciones de frontera fija al resultado
    a.insert(a.begin(), a_fixed.begin(), a_fixed.end());
    b.insert(b.begin(), b_fixed.begin(), b_fixed.end());
    c.insert(c.begin(), 0.0);  // Condición adicional para c[0]
    d.insert(d.begin(), 0.0);  // Condición adicional para d[0]
    */
    
    // Interpolar el spline en un nuevo punto
    double xi = 0.5;
    double yi = interpolateSpline(x, y, a, b, c, d, xi);

    // Imprimir la tabla de coeficientes
    printTable(x, y, a, b, c, d);

    // Imprimir el resultado de la interpolación
    cout << "\nInterpolación en x = " << xi << ": " << yi << endl;

    return 0;
}