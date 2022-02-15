//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	2. Write a template function that takes a vector<T> vt and a vector<U> vu as
//	arguments and returns the sum of all vt[i] * vu[i]s.

#include "std_lib_facilities.h"

template<typename T, typename U>
T& sum_all(const vector<T>& vt, const vector<U>& vu)
{
	if (vt.size() != vu.size()) error("cannot sum diffferent sized vectors!");

	T sum{T()};
	for (int i = 0; i < vt.size(); ++i) sum += vt[i] * vu[i];

	return sum;
}

int main()
try {
	vector<int> v_int{ 1,2,3,4,5,6,7,8,9,10 };
	vector<double> v_double{ 1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5 };

	cout <<"Sum of both vectors: "<<sum_all(v_int, v_double) << '\n';
}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}

