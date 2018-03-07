#pragma once

#include "Matrix.h"
#include "Vector.h"

template<typename T>
int cg(Matrix<T> &A, const Vector<T> &b, Vector<T> &x, T tol, int maxite) {
	Vector<T> p = b - A.sqmatvec(x);
	Vector<T> r = p;

	T tol2 = tol * tol;
	T alpha, beta, dotr, dotr_new;

	for (int i = 0; i < maxite; i++) {
		dotr = dot(r, r);

		alpha = dotr / dot(A.sqmatvec(p), p);
		x = x + alpha * p;
		Vector<T> r_new = r - alpha * A.sqmatvec(p);
		dotr_new = dot(r_new, r_new);

		if (dotr_new < tol2)
			return i;

		beta = dotr_new / dotr;
		p = r_new + beta * p;
		r = r_new;
	}
	return -1;
}