//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	13. Write a Tracer class where its constructor prints a string and its destructor
//	prints a string.Give the strings as constructor arguments.Use it to see
//	where RAII management objects will do their job(i.e., experiment with
//	Tracers as local objects, member objects, global objects, objects allocated
//	by new, etc.).Then add a copy constructorand a copy assignment so that
//	you can use Tracer objects to see when copying is done.

//#include "std_lib_facilities.h"
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

struct Tracer {
public:
	std::string c;
	std::string d;

	Tracer(const std::string& cs, const std::string& ds) 
		: c{ cs }, d{ ds } 
	{
		std::cout << c << '\n';
	}

	Tracer(const Tracer& arg)
		: c{ arg.c }, d{ arg.d }
	{
		std::cout <<"Copy Tracer Constructed: ";
	}

	Tracer& operator=(const Tracer a)
	{
		c = a.c;
		d = a.d;
		std::cout << "Copy Tracer Assigned: ";
		return *this;
	}

	~Tracer() { std::cout << d << '\n'; }
};

Tracer t2{ "Static Storage: Constructed!", "Static Storage: Destructed!" };

void test_func()
{
	Tracer t_temp{ "Stack Storage: Constructed!", "Stack Storage: Destructed!" };
}

Tracer return_func()
{
	Tracer t_temp{ "return_func(): Constructed!", "return_func(): Destructed!" };
}

int main()
try {

	Tracer t1{ "Constructed!", "Destructed!" };
	test_func();
	Tracer* tp{ new Tracer {"Free Storage : Constructed!", "Free Storage : Destructed!"} };
	delete tp;

	Tracer t3{ "t3- Constructed", "t3- Destructed"};
	std::cout << "t1 assigned: ";
	t1=return_func();
}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "unknown exception\n";
}

