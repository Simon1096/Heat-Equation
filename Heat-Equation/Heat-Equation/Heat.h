#define _USE_MATH_DEFINES
#pragma once

#include <cmath>
#include "Vector.h"
#include "cg.h"
#include <ostream>

// I got tired
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

		double prefix = -alpha * dt / (dx * dx);
		int k = pow(m, n);

		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				if (i == j) {
					M[{i, j}] = n * prefix * -2 + 1.0;
				} else {
					for (int dim = 0; dim < k; dim++) {
						if (j == i + pow(m, dim) || j == i - pow(m, dim))
							M[{i, j}] = prefix;
					}
				}
			}
		}
	}

	Vector<double> exact(double t) const {
		Vector<double> solution(length);

		double constant = exp(-M_PI * M_PI * alpha);

		double val = constant * t;
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