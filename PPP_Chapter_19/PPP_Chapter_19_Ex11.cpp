//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	11. Design and implement a counted_ptr<T> that is a type that holds a
//	pointer to an object of type T and a pointer to a “use count”(an int)
//	shared by all counted pointers to the same object of type T.The use
//	count should hold the number of counted pointers pointing to a given
//	T.Let the counted_ptr’s constructor allocate a T object and a use count
//	on the free store.Let counted_ptr’s constructor take an argument to be
//	used as the initial value of the T elements. When the last counted_ptr
//	for a T is destroyed, counted_ptr’s destructor should delete the T.Give
//	the counted_ptr operations that allow us to use it as a pointer.This is
//	an example of a “smart pointer” used to ensure that an object doesn’t
//	get destroyed until after its last user has stopped using it.Write a set
//	of test cases for counted_ptr using it as an argument in calls, container
//	elements, etc.

//#include "std_lib_facilities.h"
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> class counted_ptr {
	T* obj;
	int* use_count;
public:
	counted_ptr(T* p);
	counted_ptr() : obj{new T{T()}}, use_count{ new int{1} } {}
	counted_ptr(counted_ptr& a);
	counted_ptr& operator = ( counted_ptr&);	// copy assignment
	counted_ptr(counted_ptr&&);	// move constructor
	counted_ptr& operator=(counted_ptr&&);	// move assignment

	T& operator*() { return *obj; }
	T* operator->();

	T* object() { return obj; }
	int* use_counter() { return use_count; }
	void destroy() { obj = nullptr; use_count = nullptr; }
	~counted_ptr();
};

template <typename T> counted_ptr<T>::counted_ptr(T* p)
	: obj{ p }, use_count{ new int{1} } {
	std::cout << "constructed " << obj << '\n';
}

template <typename T> counted_ptr<T>::counted_ptr( counted_ptr& a)
	: obj{ a.object() }, use_count{ a.use_counter() }
{
	*use_count += 1;
	std::cout << "copy constructor " << this << '\n';
}

template <typename T> counted_ptr<T>::counted_ptr(counted_ptr&& a)
	: obj{ a.object() }, use_count{ a.use_counter() }
{
	a.destroy();
}

template <typename T> counted_ptr<T>::~counted_ptr() {
	if (*use_count == 1) {
		delete obj; delete use_count;
		std::cout << "destructed " << obj << '\n';
		//std::cout << "count: " << *use_count << '\n';
	}
	else {
		*use_count -= 1;
		use_count = nullptr;
		std::cout << "released " << obj;
		obj = nullptr;
		delete obj;
		delete use_count;
		std::cout << " and destructed " << obj << '\n';
		//std::cout << "count: " << *use_count << '\n';
	}
}

template <typename T>
counted_ptr<T>& counted_ptr<T>::operator = ( counted_ptr& a)
{
	if (this == &a) return *this;
	
	*use_count -= 1;
	obj = a.object();
	use_count = a.use_counter();
	*use_count += 1;
}

void test()
{
	std::cout << "test() temp: ";
	counted_ptr<double> temp{ new double{1.99} };
	std::cout << "test() temp: ";

}

counted_ptr<double> c_p1{ new double{3.14} };

void test_f_return()
{
	std::cout << "test_f_return() temp: ";
	counted_ptr<double> temp{ new double{9.99} };
	std::cout << "test_f_return() c_p1=temp: ";
	c_p1=temp;
}

int main()
try {
	//counted_ptr<double> c_p1{ 3.14 };
	std::cout << "c_p1.use_count: " << *c_p1.use_counter() << '\n';

	counted_ptr<double> c_p2;
	c_p2 = c_p1;
	std::cout <<"c_p2=c_p1.use_count: " << *c_p1.use_counter() << '\n';

	counted_ptr<double> c_p3;
	c_p3 = c_p2;
	std::cout << "c_p3=c_p1.use_count: " << *c_p1.use_counter() << '\n';
	*c_p3 = 2.1;
	std::cout << "c_p1 value :" << *c_p1 << '\n';
	std::cout << "c_p1.use_count: " << *c_p1.use_counter() << '\n';
	std::cout << "c_p2 value :" << *c_p2 << '\n';
	std::cout << "c_p2.use_count: " << *c_p2.use_counter() << '\n';
	std::cout << "c_p3 value :" << *c_p3 << '\n';
	std::cout << "c_p3.use_count: " << *c_p3.use_counter() << '\n';

	test();
	test_f_return();

	std::cout << "c_p1 value :" << *c_p1 << '\n';
	std::cout << "c_p1.use_count: " << *c_p1.use_counter() << '\n';
	std::cout << "c_p2 value :" << *c_p2 << '\n';
	std::cout << "c_p2.use_count: " << *c_p2.use_counter() << '\n';
	std::cout << "c_p3 value :" << *c_p3 << '\n';
	std::cout << "c_p3.use_count: " << *c_p3.use_counter() << '\n';
}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "unknown exception\n";
}

