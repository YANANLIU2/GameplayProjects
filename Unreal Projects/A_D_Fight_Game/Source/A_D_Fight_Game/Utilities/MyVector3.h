#pragma
#include <iostream>
#include <math.h>
using std::ostream;
using std::istream;

// The class is to provide a container of 3 data members of the same type with some general mathematical calculations
// Friend functions in a Template class: 
// 1. pre-declare the template class itself and the friend functions to better inform the compiler and avoid linker errors
// 2. Add <> in the friend lines 
template<typename T> class MyVector3;  
template<typename T> ostream& operator<< (ostream& out, const MyVector3<T>& rhs);
template<typename T> istream& operator>> (istream& in, MyVector3<T>& rhs);
template <typename T>
class MyVector3
{
public:
	T x_;

	T y_;

	T z_;

	// Constructor 
	MyVector3() :x_(0), y_(0), z_(0) {};

	MyVector3(T x, T y, T z) :x_(x), y_(y), z_(z) {};

	// Destructor 
	~MyVector3() {};
	
	// Assignment 
	const MyVector3& operator=(const MyVector3<T>& rhs);

	// Addition
	MyVector3 operator+(const MyVector3<T>& rhs);

	// Subtraction
	MyVector3 operator-(const MyVector3<T>& rhs);

	// Multiplication
	MyVector3 operator*(const MyVector3<T>& rhs);

	// Division
	MyVector3 operator/(const MyVector3<T>& rhs);

	// Returns the length of this vector.
	double get_magnitude() const { return sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

	// Returns the square of the length of this vector (faster then magnitude).
	T get_sqr_magnitude() const { return x_ * x_ + y_ * y_ + z_ * z_; }

	// Less than
	bool operator< (const MyVector3& rhs) { return this->get_sqr_magnitude() < rhs.get_sqr_magnitude(); }
	
	// Greater than
	bool operator> (const MyVector3& rhs){ return this->get_sqr_magnitude() > rhs.get_sqr_magnitude(); }

	// Less than or equal to
	bool operator<= (const MyVector3& rhs){ return this->get_sqr_magnitude() <= rhs.get_sqr_magnitude(); }

	// Greater than or equal to
	bool operator>= (const MyVector3& rhs) { return this->get_sqr_magnitude() >= rhs.get_sqr_magnitude(); }

	// Not euqal to
	bool operator!= (const MyVector3& rhs) { return this->get_sqr_magnitude() != rhs.get_sqr_magnitude(); }

	// Addition assignment
	MyVector3& operator+= (const MyVector3& rhs);

	// Subtraction assignment
	MyVector3& operator-= (const MyVector3& rhs);

	// Division assignment
	MyVector3& operator/= (const MyVector3& rhs);

	// Multiplication assignment
	MyVector3& operator*= (const MyVector3& rhs);

	// Insertion to stream
	friend ostream& operator<<<>(ostream& out, const MyVector3<T>& rhs);

	// Extraction from stream
	friend istream& operator>><>(istream& in, MyVector3<T>& rhs);
};

template<typename T>
ostream& operator<< (ostream& out, const MyVector3<T>& rhs)
{
	out << "x: " << rhs.x_ << ", y: " << rhs.y_ << ", z: " << rhs.z_ << '\n';
	return out;
}

template <typename T>
istream& operator>> (istream& in, MyVector3<T>& rhs)
{
	T x, y, z;
	in >> x >> y >> z; 
	rhs.set_x(x);
	rhs.set_y(y);
	rhs.set_z(z);
	return in;
}

template<typename T>
MyVector3<T> MyVector3<T>::operator+(const MyVector3<T>& rhs)
{
	return MyVector3<T>(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

template<typename T>
MyVector3<T> MyVector3<T>::operator-(const MyVector3<T>& rhs)
{
	return MyVector3<T>(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
}

template<typename T>
MyVector3<T> MyVector3<T>::operator*(const MyVector3<T>& rhs)
{
	return MyVector3<T>(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_);
}

template<typename T>
MyVector3<T> MyVector3<T>::operator/(const MyVector3<T>& rhs)
{
	return MyVector3<T>(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_);
}

template <typename T>
const MyVector3<T>& MyVector3<T>::operator= (const MyVector3<T>& rhs)
{
	this->x_ = rhs.x_;
	this->y_ = rhs.y_;
	this->z_ = rhs.z_;
	return *this;
}

template<typename T>
MyVector3<T>& MyVector3<T>::operator*= (const MyVector3<T>& rhs)
{
	x_ *= rhs.x_;
	y_ *= rhs.y_;
	z_ *= rhs.z_;
	return *this;
}

template<typename T>
MyVector3<T>& MyVector3<T>::operator/= (const MyVector3<T>& rhs)
{
	x_ /= rhs.x_;
	y_ /= rhs.y_;
	z_ /= rhs.z_;
	return *this;
}

template<typename T>
MyVector3<T>& MyVector3<T>::operator-= (const MyVector3<T>& rhs)
{
	x_ -= rhs.x_;
	y_ -= rhs.y_;
	z_ -= rhs.z_;
	return *this;
}

template<typename T>
MyVector3<T>& MyVector3<T>::operator+= (const MyVector3<T>& rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;
	z_ += rhs.z_;
	return *this;
}
