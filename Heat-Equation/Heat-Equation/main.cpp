#define _SCL_SECURE_NO_WARNINGS

// I am PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "cg.h"
#include "Heat1D.h"
#include "Heat2D.h"
#include "Heat.h"
#include <chrono>

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

int main() {
	// Vector tests
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

	// Matrix tests
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

	Matrix<double> m2(2, 2);
	m2[{0, 0}] = 2;
	m2[{0, 1}] = 1;
	m2[{1, 0}] = 1;
	m2[{1, 1}] = 2;

	cout << m2 << endl;

	Vector<double> b3 = { 2, 4 };
	Vector<double> x3 = { 1, 1 };

	cout << "# of iterations " << cg(m2, b3, x3, 1e-2, 1000) << endl;
	cout << "Solution " << x3 << endl;
	cout << "Result " << m2.matvec(x3) << "\n" << endl;

	//Heat1D tests
	cout << "Matrix of Heat1D with m = 3, alpha = 0.3125 and dt = 0.1" << endl;
	cout << Heat1D(0.3125, 0.1, 3).M << "\n" << endl;

	// Heat1D solutions
	Heat1D h1(0.3125, 0.001, 99);
	cout << "Exact solution:\n" << h1.exact(1) << endl;
	cout << "Numerical solution:\n" << h1.solve(1) << endl;

	// Heat2D tests
	cout << "Matrix of Heat2D with m = 3, alpha = 0.3125 and dt = 0.1" << endl;
	cout << Heat2D(0.3125, 0.1, 3).M << "\n" << endl;

	// Heat2D solutions
	Heat2D h2(0.3125, 0.001, 99);
	//cout << "Exact solution:\n" << h2.exact(0.5) << endl;
	cout << "Numerical solution:\n" << h2.solve(0.5) << endl;
	
	// Heat generic amount of dimensions test (1, 2 and 3)
	Heat<1> heat1(0.3125, 0.1, 3);
	cout << heat1.M << endl;

	Heat<2> heat2(0.3125, 0.1, 3);
	cout << heat2.M << endl;

	Heat<3> heat3(0.3125, 0.1, 3);
	cout << heat3.M << endl;
	
	system("pause");
	return 0;
}
