
#include <iostream>
#include <math.h>
#include <locale.h>
#include <iomanip>
using namespace std;

double f(double x) {
    return x * x / 2 - cos(x);
}

double fl(double x) { // f'(x)
    return x + sin(x);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите эпсилон:" << endl;
    double epsilon;
    cin >> epsilon;

    double A = -1;
    double B = 2;

    double X;

    int i = 0;
    if (fl(A) >= 0) { //проверка-функция возрастает- a это и есть минимум
        X = A;
        cout << "X_min = " << fixed << setprecision(5) << X << endl;
        cout << "iter = " << fixed << setprecision(0) << i << endl;
        cout<< "f'(X_min) = " << fixed << setprecision(5) << fl(X) << endl;
        cout << "Номер итерации: " << fixed << setprecision(0) << i << endl;
        cout << "A: " << fixed << setprecision(0) << A << endl;
        cout << "B: " << fixed << setprecision(0) << B << endl;
        return 0;
    }

    if (fl(B) <= 0) { //проверка-функция убывает - b это и есть минимум 
        X = B;
        cout << "X_min = " << fixed << setprecision(5) << X << endl;
        cout << "iter = " << fixed << setprecision(0) << i << endl;
        cout<< "f'(X_min) = " << fixed << setprecision(6) << fl(X);
        cout << "Номер итерации: " << fixed << setprecision(0) << i << endl;
        cout << "A: " << fixed << setprecision(0) << A << endl;
        cout << "B: " << fixed << setprecision(0) << B << endl;
        return 0;
    }


    while (true) {
        i++;
        X = ((A * fl(A) - f(A)) - (B * fl(B) - f(B))) / (fl(A) - fl(B));
        if (fl(X) < -epsilon) {
            A = X;
        }
        else if (fl(X) > epsilon) {
            B = X;
        }
        else if (abs(fl(X)) <= epsilon) {
            break;
        }
    }

    double x_epsilon = (A + B) / 2;

    cout << endl;
    cout << "Номер итерации: " << fixed << setprecision(0) << i << endl;
    cout << "A: " << fixed << setprecision(0) << A << endl;
    cout << "B: " << fixed << setprecision(0) << B << endl;
    cout << "X: " << fixed << setprecision(5) << X << endl;
    cout << "f'(X): " << fixed << setprecision(5) << fl(X) << endl;
    cout << "x_epsilon: " << fixed << setprecision(5) << x_epsilon << endl;
    cout << "f(x_epsilon): " << fixed << setprecision(5) << f(x_epsilon) << endl;
}

