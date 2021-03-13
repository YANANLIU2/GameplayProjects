#pragma once
#include <iostream>
#include <math.h>
using std::ostream;
using std::istream;

// The class is to provide a container of 2 data members of the same type with some general mathematical calculations
// Friend functions in a Template class: 
// 1. pre-declare the template class itself and the friend functions to better inform the compiler and avoid linker errors
// 2. Add <> in the friend lines 

template<typename T> class MyVector2;  

template<typename T> ostream& operator<< (ostream& out, const MyVector2<T>& rhs);

template<typename T> istream& operator>> (istream& in, MyVector2<T>& rhs);

template <typename T>
class MyVector2
{
public:
	T x_;

	T y_;

	// Constructor 
	MyVector2() :x_(0), y_(0) {};

	MyVector2(T x, T y) :x_(x), y_(y) {};

	// Destructor 
	~MyVector2() {};

	// Assignment 
	const MyVector2& operator=(const MyVector2<T>& rhs);

	// Addition
	MyVector2 operator+(const MyVector2<T>& rhs);

	// Subtraction
	MyVector2 operator-(const MyVector2<T>& rhs);

	// Multiplication
	MyVector2 operator*(const MyVector2<T>& rhs);

	// Division
	MyVector2 operator/(const MyVector2<T>& rhs);

	// Returns the length of this vector.
	inline double get_magnitude() const { return sqrt(x_ * x_ + y_ * y_); }

	// Returns the square of the length of this vector (faster then magnitude).
	inline T get_sqr_magnitude() const { return x_ * x_ + y_ * y_; }

	// Less than
	bool operator< (const MyVector2& rhs) { return this->get_sqr_magnitude() < rhs.get_sqr_magnitude(); }
	
	// Greater than
	bool operator> (const MyVector2& rhs){ return this->get_sqr_magnitude() > rhs.get_sqr_magnitude(); }

	// Less than or equal to
	bool operator<= (const MyVector2& rhs){ return this->get_sqr_magnitude() <= rhs.get_sqr_magnitude(); }

	// Greater than or equal to
	bool operator>= (const MyVector2& rhs) { return this->get_sqr_magnitude() >= rhs.get_sqr_magnitude(); }

	// Not euqal to
	bool operator!= (const MyVector2& rhs) { return this->get_sqr_magnitude() != rhs.get_sqr_magnitude(); }

	// Addition assignment
	MyVector2& operator+= (const MyVector2& rhs);

	// Subtraction assignment
	MyVector2& operator-= (const MyVector2& rhs);

	// Division assignment
	MyVector2& operator/= (const MyVector2& rhs);

	// Multiplication assignment
	MyVector2& operator*= (const MyVector2& rhs);

	// Insertion to stream
	friend ostream& operator<<<>(ostream& out, const MyVector2<T>& rhs);

	// Extraction from stream
	friend istream& operator>><>(istream& in, MyVector2<T>& rhs);
};

template<typename T>
ostream& operator<< (ostream& out, const MyVector2<T>& rhs)
{
	out << "x: " << rhs.x_ << ", y: " << rhs.y_ << ", z: " << rhs.z_ << '\n';
	return out;
}

template <typename T>
istream& operator>> (istream& in, MyVector2<T>& rhs)
{
	T x, y, z;
	in >> x >> y >> z; 
	rhs.set_x(x);
	rhs.set_y(y);
	rhs.set_z(z);
	return in;
}

template<typename T>
MyVector2<T> MyVector2<T>::operator+(const MyVector2<T>& rhs)
{
	return MyVector2<T>(x_ + rhs.x_, y_ + rhs.y_);
}

template<typename T>
MyVector2<T> MyVector2<T>::operator-(const MyVector2<T>& rhs)
{
	return MyVector2<T>(x_ - rhs.x_, y_ - rhs.y_);
}

template<typename T>
MyVector2<T> MyVector2<T>::operator*(const MyVector2<T>& rhs)
{
	return MyVector2<T>(x_ * rhs.x_, y_ * rhs.y_);
}

template<typename T>
MyVector2<T> MyVector2<T>::operator/(const MyVector2<T>& rhs)
{
	return MyVector2<T>(x_ / rhs.x_, y_ / rhs.y_);
}

template <typename T>
const MyVector2<T>& MyVector2<T>::operator= (const MyVector2<T>& rhs)
{
	x_ = rhs.x_;
	y_ = rhs.y_;
	return *this;
}

template<typename T>
MyVector2<T>& MyVector2<T>::operator*= (const MyVector2<T>& rhs)
{
	x_ *= rhs.x_;
	y_ *= rhs.y_;
	return *this;
}

template<typename T>
MyVector2<T>& MyVector2<T>::operator/= (const MyVector2<T>& rhs)
{
	x_ /= rhs.x_;
	y_ /= rhs.y_;
	return *this;
}

template<typename T>
MyVector2<T>& MyVector2<T>::operator-= (const MyVector2<T>& rhs)
{
	x_ -= rhs.x_;
	y_ -= rhs.y_;
	return *this;
}

template<typename T>
MyVector2<T>& MyVector2<T>::operator+= (const MyVector2<T>& rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;
	return *this;
}
