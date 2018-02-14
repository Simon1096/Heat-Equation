#pragma once

#include <stdexcept>
#include <ostream>
#include <map>

#include "Vector.h"

using namespace std;

template<typename T>
class Matrix {
public:

	const int rows;
	const int cols;
	map<array<int, 2>, T> map;

	Matrix(int n, int m) : rows(n), cols(m) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				map[{i, j}] = 0;
	}


	T& operator[](const array<int, 2> idx) {
		return map[idx];
	}

	template<typename T>
	Vector<T> matvec(const Vector<T> &v) {
		if (cols != v.length)
			throw invalid_argument("Size of vector not equal to number of columns in matrix.");

		Vector<T> out(rows);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				out.data[i] += v.data[j] * map[{i, j}];
		return out;
	}
};