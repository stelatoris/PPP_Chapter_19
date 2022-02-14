//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	1. Write a template function f() that adds the elements of one vector<T> to
//	the elements of another; for example, f(v1, v2) should do v1[i] += v2[i] for
//	each element of v1.

#include "std_lib_facilities.h"

template <typename T>
void f(vector<T>& v1, const vector<T>& v2)
{
	for (int i = 0; i < v2.size(); ++i) {
		if (i > v1.size() - 1) v1.push_back(v2[i]);
		else {
			v1[i] += v2[i];
		}
	}
}

template <typename T>
void print_vector(const vector<T>& v)
{
	for (int i{}; i < v.size(); ++i) {
		cout << v[i];
		if (i < v.size() - 1) cout << ", ";
		if (i == v.size() - 1) cout << '\n';
	}
}

int main()
{
	// int
	vector<int> v_int1{ 1,2,3,4,5,6,7,8,9 };
	vector<int> v_int2{ 5,5,5,5,5 };
	f(v_int1, v_int2);
	print_vector(v_int1);

	// double
	vector<double> v_double1{ 1.1,2.2,3.3,4.4,5.5 };
	vector<double> v_double2{ 5.5,5.5,5.5,5.5,5.5,5.5,5.5,5.5,5.5,5.5,5.5 };
	f(v_double1, v_double2);
	print_vector(v_double1);

	// string
	vector<string> v_string1{ "Mr. ", "Miss. ", "Dr. " };
	vector<string> v_string2{ "Anderson", "Perry", "Strange" };
	f(v_string1, v_string2);
	print_vector(v_string1);

	char ch1='a';
	char ch2 = 'a';
	char ch3 = ch1 + ch2;
	cout << ch1<<',' << ch2 << '\n';
	cout <<"ch1+ch2=" << ch1 + ch2 << '\n';
	cout << "ch3: " << ch3 << '\n';
}

