#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;

double nevilleInterpolation(const vector<double>& x, const vector<double>& y, double xi){
    int n = x.size();
    vector<double> p(n);

    for (int i = 0; i < n; ++i){
        p[i] = y[i];
    }

    cout << setw(5) << "Iter";
    for (int i = 0; i < n; ++i){
        cout << setw(13) << "p[" << i << "]"; 
    }
    cout << endl;

    for (int k = 1; k < n; ++k){
        cout << setw(5) << k ;
        for (int i = 0; i < n - k; ++i){
            p[i] = ((xi - x[i + k]) * p[i] + (x[i] - xi) * p[i + 1]) / (x[i] - x[i + k]);
            cout << setw(15) << p[i];
        }
        cout << endl;
    }

    return p[0];
}

int main(){
    vector<double> x = {1.0, 2.0, 3.0, 4.0, 6.0}; // Valores de x conocidos
    vector<double> y = {exp(1.0), exp(2.0), exp(3.0), exp(4.0), exp(6.0)}; // Valores de y conocidos {exp(1.0), exp(2.0), exp(3.0), exp(4.0), exp(6.0)
    double xi = 2.5; // Valor objetivo para interpolar
    double interpolatedValue = nevilleInterpolation(x, y, xi);
    
    cout << endl;
    cout << "Valor interpolado en xi = " << xi << " es: " << interpolatedValue << endl;

    return 0;
}