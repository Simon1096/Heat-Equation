#define _USE_MATH_DEFINES
#pragma once

#include <cmath>
#include "Vector.h"
#include "cg.h"
#include <ostream>

using namespace std;

template<int n>
class Heat {

public:

	double alpha, dt, dx;
	int m;
	int length;

	Matrix<double> M;

	Heat(double alpha, double dt, int m) : M(pow(m, n), pow(m, n)) {
		this->alpha = alpha;
		this->dt = dt;
		this->m = m;
		this->length = pow(m, n);
		this->dx = 1.0 / (m + 1);

		int k = pow(m, n);
		double prefix = -alpha * dt / (dx * dx);
		for (int i = 0; i < length; i++) {
			M[{i, i}] = -2 * n * prefix + 1.0;
			for (int j = 0; j < k; j++) {
				if (i - pow(m, j) >= 0)
					M[{i, i - (int)pow(m, j)}] = prefix;
				if (i + pow(m, j) < length)
					M[{i, i + (int)pow(m, j)}] = prefix;
			}
		}
	}

	Vector<double> exact(double t) const {
		Vector<double> solution(length);

		double constant = exp(-M_PI * M_PI * alpha);

		for (int i = 0; i < length; i++)
			solution.data[i] = sin((i + 1)*dx*M_PI) * constant;

		return solution;
	}

	Vector<double> solve(double t_end) const {
		Vector<double> solution(length);

		for (int i = 0; i < length; i++)
			solution.data[i] = sin((i + 1) * dx * M_PI);

		int steps = t_end / dt;
		for (int i = 0; i <= steps; i++)
			cg(const_cast<Matrix<double>&>(M), solution, solution, 1e-3, 100);
		return solution;
	}
};