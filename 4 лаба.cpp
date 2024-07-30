#include<iostream>
#include <math.h>
using namespace std;

class Vector2 { //вектор
public:
	double* x;
	Vector2(double* x) : x(x) {}
	Vector2(double x1, double x2) :x(new double[2]{ x1, x2 }) {} //конструктор для матрицы
	~Vector2() { if (!x) delete[] x; } //деструктор

	double& operator[](const int i);
	Vector2& operator- (Vector2 x1);

	double norm();
	void print();
};
class Matrix2 {
public:
	double** M;
	Matrix2(double** M) : M(M) {}
	Matrix2(double a11, double a12, double a21, double a22)
		:M(new double* [2]{
			new double[2] {a11, a12},
			new double[2] {a21, a22}
			})
	{}
	Matrix2(const Matrix2& M1) : M(new double* [2]{
			new double[2] {M1.M[0][0], M1.M[0][1]},
			new double[2] {M1.M[1][0], M1.M[1][1]}
		})
	{}
	~Matrix2() { if (!M) { delete[] M[0], M[1], M; } }

	double* operator[](const int i);
	Matrix2& operator= (const Matrix2& M1);
	Vector2& operator* (Vector2 x);

	Matrix2 inverse();
	void print();
};

double f(Vector2 x) { //функция
	return x[0] * x[0] + 3 * x[1] * x[1] + cos(x[0] + x[1]);
}
Vector2 f1(Vector2 x) {// производная dx1,dx2
	return Vector2(2 * x[0] -sin(x[0] + x[1]),
		6 * x[1] - sin(x[0] + x[1]));
}
Matrix2 f2(Vector2 x) { // dx1^2,dx1dx2,dx2^2,dx1dx2
	return Matrix2(2 - cos(x[0] + x[1]), -cos(x[0] + x[1]),
		-cos(x[0] + x[1]), 6 - cos(x[0] + x[1])
	);
}

int main() {
	setlocale(LC_ALL, "Russian");
	double eps = 0.00000001;
	Vector2 x(0, 0);


	cout << "Введите x0" << endl;
	cin >> x[0];
	cout << "Введите x1"<<endl;
	cin >> x[1];
	//cout << endl << "Введите точность ";
	//cin >> eps;
	//cout << endl;
	for (int i = 0; f1(x).norm() > eps; i++, // условие выхода
		x = x - f2(x).inverse() * f1(x)) //xn+1
	{
		cout << "Итерация " << i << endl;
		cout << "||f'(x)|| = " << f1(x).norm() << endl;
		cout << "f'(x) = "; f1(x).print();
		cout << "x = "; x.print();
		cout << "_____________________________" << endl;
	}
	
	cout << endl << endl;
	cout << "||f'(x)|| = " << f1(x).norm() << endl;
	cout << "f'(x) = ";f1(x).print();
	cout << "x = ";x.print();
	cout << "_____________________________" << endl;

}
double& Vector2::operator[] (const int i) {
	return x[i];
}
Vector2& Vector2::operator- (Vector2 x1) {
	Vector2* res = new Vector2(x[0] - x1[0], x[1] - x1[1]);
	return *res;
}
double Vector2::norm() {
	return sqrt(x[0] * x[0] + x[1] * x[1]);
}
void Vector2::print() {
	cout << x[0] << ' ' << x[1] << endl;
}

double* Matrix2::operator[] (const int i) {
	return M[i];
}
Matrix2& Matrix2::operator= (const Matrix2& M1) {
	M[0][0] = M1.M[0][0];
	M[0][1] = M1.M[0][1];
	M[1][0] = M1.M[1][0];
	M[1][1] = M1.M[1][1];
	return *this;
}
Vector2& Matrix2::operator* (Vector2 x) {
	Vector2* v = new Vector2(M[0][0] * x[0] + M[0][1] * x[1],
		M[1][0] * x[0] + M[1][1] * x[1]);
	return *v;
}
Matrix2 Matrix2::inverse() {
	double det = M[0][0] * M[1][1] - M[1][0] * M[0][1];
	Matrix2	M1(M[1][1] / det, -M[0][1] / det,
		-M[1][0] / det, M[0][0] / det);
	*this = M1;
	return M1;
}
void Matrix2::print() {
	cout << M[0][0] << ' ' << M[0][1] << endl;
	cout << M[1][0] << ' ' << M[1][1] << endl;
}