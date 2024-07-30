

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


const double Lm = (1 + sqrt(5)) / 2;

double function(double x) {
    return  pow(x, 2) / 2 - cos(x);
}

int main() {
    long nIteration = 1;
    double a, b;
    double eps = 0.0001;
    cout << "Enter a : "; cin >> a;
    cout << "Enter b : "; cin >> b;
    while (fabs(b - a) >= 2 * eps) {
        double d = (b - a) / (Lm * Lm);
        double x1 = a + d;
        double x2 = b - d;
        double fx = function(x1);
        double fy = function(x2);
        cout << "Iteration: " << (nIteration++) << endl;
        cout << "A =" << a << endl;
        cout << "B =" << b << endl;
        cout << "x1 =  " << fixed << setprecision(4) << x2 << endl;
        cout << "x2 =  " << fixed << setprecision(4) << x2 << endl;
        cout << "function(x1) = " << fixed << setprecision(0) << function(x1) << endl;
        cout << "function(x2) = " << fixed << setprecision(0) << function(x2) << endl << endl;
        if (function(x1) > function(x2)) {
            a = x1;
            x1 = x2;
            fx = fy;
            x2 = a + b - x1;
        }
        else {
            b = x2;
            x2 = x1;
            fy = fx;
            x1 = a + b - x2;
        }
    }
    double  xmin = (a + b) * 0.5;
    cout << endl << endl;
    cout << "xmin = " << fixed << setprecision(4) << xmin << endl << "function(xmin) = " << fixed << setprecision(0) << function((a + b) / 2) << endl;

    return 0;
}