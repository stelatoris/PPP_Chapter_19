//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	6. Repeat the previous exercise, but with a class Number<T> where T can be
//	any numeric type.Try adding% to Number and see what happens when
//	you try to use % for Number<double>and Number<int>.

#include "std_lib_facilities.h"

template<typename T>
class Number {
	T val;
public:
	Number(T value) : val{ value } {}
	Number() : val{ T() } {}

	T get() const { return val; }

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
//--------------------------------------------

int main()
try {
	Number<double> n1{ 5.2 };
	Number<double> n2 = 10.7;
	Number<double> n3 = n1;
	Number<double> n4{ n2 };

	cout << "double n1: " << n1 << '\n';
	cout << "double n2: " << n2 << '\n';
	cout << "double n3: " << n3 << '\n';
	cout << "double n4: " << n4 << '\n';
	cout << "double n1 + double n2=" << n1 + n2 << '\n';

	Number<int> n_int1 = 12;
	Number<int> n_int2 = 5;
	Number<double>n_dble1 = 10.5;
	cout << "double n_dble1 % int n_int2=" << n_dble1 % n_int2 << '\n';

	cout << "double n1+ int n_int1=" << n1 + n_int1 << '\n';


	Number<double> n5;
	cout << "Please enter a numerical value: \n";
	cin >> n5;
	cout << "You entered " << n5 << '\n';

	if (n5 < n2) cout << n2 << " is larger than " << n5 << "!\n";
	else if (n5 > n2) cout << n2 << " is smaller than " << n5 << "!\n";
	else if (n5 == n2) cout << n2 << " is equal to " << n5 << "!\n";


}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}