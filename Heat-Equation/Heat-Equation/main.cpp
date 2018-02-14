#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, Vector<T> &v) {
	if (v.length == 0)
		return os << "[Empty vector]";
	os << "[";
	for (int i = 0; i < v.length; i++)
		os << v.data[i] << " ";
	return os << "\b]";
}

template<typename T>
ostream &operator<<(ostream &os, Matrix<T> &m) {
	if (m.rows == 0 || m.cols == 0)
		return os << "[[Empty matrix]]";
	os << "[";
	for (int i = 0; i < m.rows; i++) {
		os << "[";
		for (int j = 0; j < m.cols; j++)
			os << m[{i, j}] << " ";
		os << "\b]\n";
	}
	return os << "]";
}

template<typename T>
int cg(Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxite) {
	Vector<T> p = b - A.matvec(x);
	Vector<T> r = p;

	T tol2 = tol * tol;
	T alpha, beta, dotr, dotr_new;

	for (int i = 0; i < maxite; i++) {
		dotr = dot(r, r);

		alpha = dotr / dot(A.matvec(p), p);
		x = x + alpha * p;
		Vector<T> r_new = r - alpha * A.matvec(p);
		dotr_new = dot(r_new, r_new);

		if (dotr_new < tol2)
			return i;

		beta = dotr_new / dotr;
		p = r_new + beta * p;
		r = r_new;
	}
	return -1;
}

int main() {
	/*
	Vector<int> v;
	cout << "Default constructor\n" << v << "\n" << endl;

	Vector<int> v2(5);
	cout << "Constructor with length\n" << v2 << "\n" << endl;

	Vector<int> v3({ 1,2,3,4 });
	cout << "Constructor with list\n" << v3 << "\n" << endl;

	Vector<int> v4 = { 1,2,3,4 };
	cout << "Constructor with list 2\n" << v4 << "\n" << endl;

	Vector<int> v5(v2);
	cout << "Constructor with vector\n" << v5 << "\n" << endl;

	Vector<int> v6 = v4;
	cout << "Constructor with vector 2\n" << v6 << "\n" << endl;

	cout << "Dot product:\n" << dot(v3, v4) << endl;

	cout << "Addition\n" << (v3 + v4) << "\n" << endl;

	cout << "Subtraction\n" << (v3 - v4) << "\n" << endl;

	cout << "Right hand multiplication\n" << (v3 * 3) << endl;
	cout << "Right hand multiplication with double\n" << (v3 * 3.5) << "\n" << endl;

	cout << "Left hand multiplication\n" << (3 * v3) << endl;
	cout << "Left hand multiplication with double\n" << (3.5 * v3) << "\n" << endl;
	*/
	Matrix<int> map(2, 2);

	map[{0, 0}] = 0;
	map[{0, 1}] = 1;
	map[{1, 0}] = 2;
	map[{1, 1}] = 3;

	cout << map[{1, 1}] << endl;
	cout << map << endl;
	map[{1, 1}] = 42;
	cout << map[{1, 1}] << "\n" << endl;

	Vector<int> vec = { 2, 2 };
	cout << "Matvec:" << map.matvec(vec) << "\n" << endl;

	Matrix<double> identity(2, 2);
	identity[{0, 0}] = 2;
	identity[{1, 1}] = 2;

	Vector<double> b = { 2, 4 };
	Vector<double> x = { 1, 1 };

	cout << "# of iterations " << cg(identity, b, x, 1.0, 1000) << endl;
	cout << "Solution " << x << endl;
	cout << "Result " << identity.matvec(x) << "\n" << endl;


	Matrix<double> m(2, 2);
	m[{0, 0}] = 4;
	m[{0, 1}] = 1;
	m[{1, 0}] = 1;
	m[{1, 1}] = 3;

	Vector<double> b2 = { 1, 2 };
	Vector<double> x2 = { 2, 1 };

	cout << "# of iterations " << cg(m, b2, x2, 1e-2, 1000) << endl;
	cout << "Solution " << x2 << endl;
	cout << "Result " << m.matvec(x2) << "\n" << endl;

	system("pause");
	return 0;
}
