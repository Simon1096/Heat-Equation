#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include "Vector.h"

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, Vector<T> &v) {
	if (v.length == 0)
		return os << "[Empty vector]";
	os << "[";
	for (int i = 0; i < v.length; i++)
		os << v.data[i] << ", ";
	return os << "\b\b]";
}

int main() {
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

	system("pause");
	return 0;
}
