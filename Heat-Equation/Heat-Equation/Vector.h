#pragma once

#include <array>
#include <memory>
#include <stdexcept>
#include <ostream>

using namespace std;

template<typename T>
class Vector {
public:
	int length;
	T* data;

	Vector() {
		length = 0;
		data = new T[0];
		data[0] = 0;
	}

	Vector(int l) {
		length = l;
		data = new T[length];
		for (int i = 0; i < length; i++)
			data[i] = 0;
	}

	Vector(const initializer_list<T> list) : Vector((int)list.size()) {
		uninitialized_copy(list.begin(), list.end(), data);
	}

	Vector(const Vector<T> &other) {
		length = other.length;
		data = other.data;
	}

	Vector& operator=(const Vector v) {
		if (this != &c) {
			delete[] data;
			data = new T[v.length];
			length = v.length;

			copy(v.data, v.data + length, data);
		}
		return *this;
	}

	Vector operator+(const Vector<T> &v) {
		if (length != v.length)
			throw invalid_argument("Unequal vector lengths");
		Vector<T> out(length);
		for (int i = 0; i < length; i++)
			out.data[i] = data[i] + v.data[i];
		return out;
	}

	Vector operator-(const Vector<T> &v) {
		if (length != v.length)
			throw invalid_argument("Unequal vector lengths");
		Vector<T> out(length);
		for (int i = 0; i < length; i++)
			out.data[i] = data[i] - v.data[i];
		return out;
	}

	template<typename U>
	auto operator*(U scalar) -> Vector<decltype(scalar * data[0])> {
		auto type = scalar * data[0];
		Vector<decltype(type)> out(length);
		for (int i = 0; i < length; i++)
			out.data[i] = scalar * data[i];
		return out;
	}
};
template<typename T>
T dot(const Vector<T> &l, const Vector<T> &r) {
	if (l.length != r.length)
		throw invalid_argument("Unequal vector lengths");
	T out = 0;
	for (int i = 0; i < l.length; i++)
		out += l.data[i] * r.data[i];
	return out;
}

template<typename U, typename T>
inline auto operator*(U scalar, Vector<T> &v) -> Vector<decltype(scalar * v.data[0])> {
	auto type = scalar * v.data[0];
	Vector<decltype(type)> out(v.length);
	for (int i = 0; i < v.length; i++)
		out.data[i] = scalar * v.data[i];
	return out;
}