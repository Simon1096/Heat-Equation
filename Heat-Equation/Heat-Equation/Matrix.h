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
	T** data;
	map<array<int, 2>, T> map;

	Matrix(int n, int m) : rows(n), cols(m) {
		data = new T*[n];
		for (int i = 0; i < n; i++) {
			T* row = new T[m];
			fill(row, row + m, 0);
			data[i] = row;
		}
	}


	T& operator[](const array<int, 2> idx) {
		return data[idx[0]][idx[1]];
	}

	template<typename T>
	Vector<T> matvec(const Vector<T> &v) {
		if (cols != v.length)
			throw invalid_argument("Size of vector not equal to number of columns in matrix.");

		Vector<T> out(rows);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				out.data[i] += v.data[j] * data[i][j];
		return out;
	}

	template<typename T>
	Vector<T> sqmatvec(const Vector<T> &v) {
		if (cols != v.length)
			throw invalid_argument("Size of vector not equal to number of columns in matrix.");

		if (cols != rows)
			throw invalid_argument("Matrix is not square.");

		Vector<T> out(rows);
		for (int i = 0; i < rows; i++) {
			out.data[i] += v.data[i] * data[i][i];
			if (i - 1 >= 0)
				out.data[i] += v.data[i - 1] * data[i][i - 1];
			if (i + 1 < rows)
				out.data[i] += v.data[i + 1] * data[i][i + 1];
		}
		return out;
	}
};