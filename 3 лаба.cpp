
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

// наша функция 
double f(double x1, double x2) {
    return pow(x1, 2) + 3 * pow(x2, 2) + cos(x1 + x2);
}
//Первая производная по dx1
double dfx1(double x1, double x2) {
    return 2 * x1 - sin(x1 + x2);
}
//Первая производная по dx2
double dfx2(double x1, double x2) {
    return 6 * x2 - sin(x1 + x2);
}

double gk1(double x1, double x2) { return dfx1(x1, x2); }
double gk2(double x1, double x2) { return dfx2(x1, x2); }

double xk1(double x1, double x2, double s) {
    return x1 - s * gk1(x1, x2);
}

double xk2(double x1, double x2, double s) {
    return x2 - s * gk2(x1, x2);
}

double fs(double x1, double x2, double s) {
    return pow(x1 - s * gk1(x1, x2), 2) + 3 * pow(x2 - s * gk2(x1, x2), 2) + cos(x1 - s * gk1(x1, x2) + x2 + s * gk2(x1, x2));
}

double n(double x1, double x2) {
    return sqrt(pow(gk1(x1, x2), 2) + pow(gk2(x1, x2), 2));
}

double Section(double a, double x1, double x2, double g1, double g2, double epsilon) { // для нахождения s
    double h = 10;
    double b = a + h;
    double x1_a = x1;
    double x2_a = x2;
    double x1_b = x1 - b * g1;
    double x2_b = x2 - b * g2;
    while (f(x1_a, x2_a) > f(x1_b, x2_b)) {
        b += h;
        h *= 2;
        x1_b = x1 - b * g1;
        x2_b = x2 - b * g2;
    }

    double lambda = (1 + sqrt(5)) / 2;
    double delta = (b - a) / (lambda * lambda);

    double A = a;
    double B = b;

    double X = A + delta;
    double Y = B - delta;

    double x1_x = x1 - X * g1;
    double x2_x = x2 - X * g2;
    double x1_y = x1 - Y * g1;
    double x2_y = x2 - Y * g2;

    while (B - A > 2 * epsilon) {
        if (f(x1_x, x2_x) > f(x1_y, x2_y)) {
            A = X;
            X = Y;
            Y = A + B - X;

            x1_x = x1 - X * g1;
            x2_x = x2 - X * g2;
            x1_y = x1 - Y * g1;
            x2_y = x2 - Y * g2;
        }
        else {
            B = Y;
            Y = X;
            X = A + B - Y;

            x1_x = x1 - X * g1;
            x2_x = x2 - X * g2;
            x1_y = x1 - Y * g1;
            x2_y = x2 - Y * g2;
        }
    }

    return (A + B) / 2;
}

double min(double x1, double x2, double B) {
    double A = 0, eps = 0.000001;
    double l = (1 + pow(5, 0.5)) / 2; //лямбда
    double delta = (B - A) / (l * l); //дельта

    double Y = B - delta; //из док-ва з.с
    double X = A + delta;

    double FX = fs(x1, x2, X);
    double FY = fs(x1, x2, Y);

    while (B - A > 2 * eps) { //метод золотого сечения
        if (FX > FY) {
            A = X; X = Y; FX = FY; Y = A + B - X; FY = fs(x1, x2, Y);
        }
        else {
            B = Y; Y = X; FY = FX; X = A + B - Y; FX = fs(x1, x2, X);
        }
    }
    double Xeps = (A + B) / 2;

    return Xeps;
}

int main() {
    double x0 = 1, y0 = 1;
    double eps = 0.000001;
    double x, y, x1min, x2min, s0;
    int i = 0;

    double h = 10;
 //алгоритм
        while (n(x0, y0) > eps) {
            i++;

            s0 = Section(0, x0, y0, gk1(x0, y0), gk2(x0, y0), eps);
            x = xk1(x0, y0, s0);
            y = xk2(x0, y0, s0);

            x0 = x; y0 = y;
            cout << i << " z = (" << x0 << ";" << y0 << ")" << " f(z) = " << f(x0, y0) << " ||f'(z)|| = " << n(x0, y0) << ")\n";
        }

   x1min = x; x2min = y;
    cout << "min = (" << x1min << ";" << x2min << ")";

    return 0;
}
