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
			for (int j = 0; j < m*m; j++) {
				if (i == j) {
					M[{i, j}] = prefix * -4 + 1.0;
				} else if (j == i + 1 || j == i - 1)
					M[{i, j}] = prefix;
				else if (j == i + m || j == i - m)
					M[{i, j}] = prefix;
			}
		}
	}

	Vector<double> exact(double t) const {
		Vector<double> solution(m*m);

		double constant = exp(-M_PI * M_PI * alpha);

		double val = constant * t;
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