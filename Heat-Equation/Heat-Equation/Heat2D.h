#define _USE_MATH_DEFINES
#pragma once

#include <cmath>
#include "Vector.h"
#include "cg.h"
#include <ostream>

using namespace std;

class Heat2D {

public:

	double alpha, dt, dx;
	int m;

	Matrix<double> M;

	Heat2D(double alpha, double dt, int m) : M(m*m, m*m) {
		this->alpha = alpha;
		this->dt = dt;
		this->m = m;
		this->dx = 1.0 / (m + 1);

		double prefix = -alpha * dt / (dx * dx);
		for (int i = 0; i < m*m; i++) {
			M[{i, i}] = -4 * prefix + 1.0;
			if (i - 1 >= 0)
				M[{i, i - 1}] = prefix;
			if (i + 1 < m*m)
				M[{i, i + 1}] = prefix;
			if (i - m >= 0)
				M[{i, i - m}] = prefix;
			if (i + m < m*m)
				M[{i, i + m}] = prefix;
		}
	}

	Vector<double> exact(double t) const {
		Vector<double> solution(m*m);

		double constant = exp(-M_PI * M_PI * alpha);

		for (int i = 0; i < m*m; i++)
			solution.data[i] = sin((i + 1)*dx*M_PI) * constant;

		return solution;
	}

	Vector<double> solve(double t_end) const {
		Vector<double> solution(m*m);

		for (int i = 0; i < m*m; i++)
			solution.data[i] = sin((i + 1) * dx * M_PI);

		int steps = t_end / dt;
		for (int i = 0; i <= steps; i++)
			cg(const_cast<Matrix<double>&>(M), solution, solution, 1e-3, 100);
		return solution;
	}
};