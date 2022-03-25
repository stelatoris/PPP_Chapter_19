//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	10. Implement a simple unique_ptr supporting only a constructor, destructor,
//	– > , *, and release().In particular, don’t try to implement an assignment
//	or a copy constructor.

//#include "std_lib_facilities.h"
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename T> class unique_ptr {
	T* p;
public:
	unique_ptr(T v) : p{ new T {v} } { std::cout << "constructed " << p << '\n'; }
	unique_ptr() : p{ new T {T()} } {}
	T* release() { T* temp = p; p = nullptr; return temp; }
	
	~unique_ptr() { std::cout << "destructed "<<p<<'\n';  delete p; }
	
	T* get() { return p; }
	T& operator*() { return *p; }
	T* operator->();
};

template<typename T>
std::ostream& operator<<(std::ostream& os, unique_ptr<T>& p)
{
	return os << p.get();;
}

int main()
try {
	unique_ptr<int> up_int1{ 10 };
	int* p_int = new int{ 20 };

	std::cout <<"up_int1: " << up_int1 << '\n';
	std::cout <<"*up_int1: "<< * up_int1 << '\n';
	
	unique_ptr<int> up_int2{20};
	std::cout <<  up_int2 << '\n';
	std::cout << up_int2.release() << '\n';
	std::cout << up_int2 << '\n';
}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "unknown exception\n";
}

