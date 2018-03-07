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

class Heat1D {

public:

	double alpha, dt, dx;
	int m;

	Matrix<double> M;

	Heat1D(double alpha, double dt, int m) : M(m, m) {
		this->alpha = alpha;
		this->dt = dt;
		this->m = m;
		this->dx = 1.0 / double(m + 1);

		double prefix = -alpha * dt / (dx * dx);
		// Construct tridiagonal matrix
		for (int i = 0; i < m; i++) {
			// Main diagonal
			M[{i,i}] = prefix * -2 + 1.0;
			// Left side diagonal
			if (i - 1 >= 0)
				M[{i, i - 1}] = prefix;
			// Right side diagonal
			if (i + 1 < m)
				M[{i, i + 1}] = prefix;
		}
	}

	Vector<double> exact(double t) const {
		Vector<double> solution(m);

		double constant = exp(-M_PI * M_PI * alpha * t);

		for (int i = 0; i < m; i++)
			solution.data[i] = sin((i + 1) * dx * M_PI) * constant;

		return solution;
	}

	Vector<double> solve(double t_end) const {
		Vector<double> solution(m);

		for (int i = 0; i < m; i++)
			solution.data[i] = sin((i + 1) * dx * M_PI);

		int steps = t_end / dt;
		for (int i = 0; i <= steps; i++)
			cg(const_cast<Matrix<double>&>(M), solution, solution, 1e-3, 100);
		return solution;
	}
};