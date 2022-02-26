//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	7. Try your solution to exercise 2 with some Numbers:
// 
//	2. Write a template function that takes a vector<T> vt and a vector<U> vu as
//	arguments and returns the sum of all vt[i] * vu[i]s.

#include "std_lib_facilities.h"

template<typename T>
class Number {
	T val;
public:
	Number(T value) : val{ value } {}
	Number() : val{ T() } {}

	T get() const { return val; }
	void set(T n) { val = n; }

	T& operator=(const T& n) { val = n; return *this; }
};

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n)
{
	return os << n.get();
}

template<typename T>
istream& operator>>(istream& is, Number<T>& n)
{
	T temp{};
	is >> temp;
	Number<T>nn{ temp };
	if (!is) return is;
	n = nn;
	return is;
}

//-----------------------------------------
template<typename T, typename U>
Number<T> operator+(const Number<T>& a, const Number<U>& b)
{
	return a.get() + b.get();
}

template<typename T, typename U>
Number<T> operator-(const Number<T>& a, const Number<U>& b)
{
	return a.get() - b.get();
}

template<typename T, typename U>
Number<T> operator*(const Number<T>& a, const Number<U>& b)
{
	return a.get() * b.get();
}

template<typename T, typename U>
Number<T> operator/(const Number<T>& a, const Number<U>& b)
{
	return a.get() / b.get();
}

template<typename T, typename U>
Number<T> operator%(const Number<T>& a, const Number<U>& b)
{
	return int(a.get()) % int(b.get());
}

template<typename T, typename U>
void operator+=(Number<T>& a, const Number<U>& b)
{	
	a.set(a.get() + b.get());
}

//------------

template<typename T, typename U>
bool operator<(const Number<T>& a, const Number<U>& b)
{
	return a.get() < b.get();
}

template<typename T, typename U>
bool operator>(const Number<T>& a, const Number<U>& b)
{
	return a.get() > b.get();
}

template<typename T, typename U>
bool operator==(const Number<T>& a, const Number<U>& b)
{
	return a.get() == b.get();
}

template<typename T, typename U>
bool operator!=(const Number<T>& a, const Number<U>& b)
{
	return a.get() != b.get();
}

template<typename T, typename U>
bool operator<=(const Number<T>& a, const Number<U>& b)
{
	return a.get() <= b.get();
}

template<typename T, typename U>
bool operator>=(const Number<T>& a, const Number<U>& b)
{
	return a.get() >= b.get();
}
//------------------------------------------------------

template<typename T, typename U>
T& sum_all(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size()) error("cannot sum diffferent sized vectors!");

	T sum{ T() };
	for (int i = 0; i < vt.size(); ++i) sum += vt[i] * vu[i];

	return sum;}

//-----------------------------------------------------

int main()
try {

	vector<Number<int>> v_int1{ 1,2,3,4,5,6,7,8,9,10 };
	vector<Number<int>> v_int2{ 1,2,3,4,5,6,7,8,9,10 };
	vector<Number<double>> v_double{ 1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5 };

	cout << "Sum of vectors v_int1 and v_double: " << sum_all(v_int1, v_double) << '\n';
	cout << "Sum of vectors v_int1 and v_int2: " << sum_all(v_int1, v_int2) << '\n';
}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}

