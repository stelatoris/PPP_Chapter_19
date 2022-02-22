//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
// 5. Define a class Int having a single member of class int. Define constructors,
// assignment, and operators + , –, *, / for it. Test it, and improve its
// design as needed(e.g., define operators << and >> for convenient I / O).

#include "std_lib_facilities.h"

class Int {
	int val;
public:	
	Int(int value) : val{value} {}
	Int() : val{int()}{}

	int get() const { return val; }

	//vector& vector::operator=(const vector& a)
	Int& operator=(const int n) { val = n; return *this; }
};

ostream& operator<<(ostream& os, const Int& n)
{
	return os << n.get();
}

istream& operator>>(istream& is, Int& n)
{
	int temp{};
	is >> temp;
	if (!is) return is;
	n = temp;
	return is;
}

//-----------------------------------------
int operator+(const Int& a, const Int& b)
{
	return a.get() + b.get();
}

int operator-(const Int& a, const Int& b)
{
	return a.get() - b.get();
}

int operator*(const Int& a, const Int& b)
{
	return a.get() * b.get();
}

int operator/(const Int& a, const Int& b)
{
	return a.get() / b.get();
}

bool operator<(const Int& a, const Int& b)
{
	return a.get() < b.get();
}

bool operator>(const Int& a, const Int& b)
{
	return a.get() > b.get();
}

bool operator==(const Int& a, const Int& b)
{
	return a.get() == b.get();
}

bool operator!=(const Int& a, const Int& b)
{
	return a.get() != b.get();
}

bool operator<=(const Int& a, const Int& b)
{
	return a.get() <= b.get();
}

bool operator>=(const Int& a, const Int& b)
{
	return a.get() >= b.get();
}
//--------------------------------------------

int main()
try {	
	Int n1{ 5 };
	Int n2 = 10;
	Int n3 = n1;
	Int n4{ n2 };
	
	cout << "n1: " << n1 << '\n';
	cout << "n2: " << n2 << '\n';
	cout << "n3: " << n3 << '\n';
	cout << "n4: " << n4 << '\n';
	cout << "n1+n2=" << n1 + n2 << '\n';

	Int n5;
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

