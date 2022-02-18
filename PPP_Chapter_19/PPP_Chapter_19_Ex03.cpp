//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	3. Write a template class Pair that can hold a pair of values of any type.
//	Use this to implement a simple symbol table like the one we used in the
//	calculator(§7.8).

#include "std_lib_facilities.h"

template<typename T, typename U>
class Symbol_Table {
public:
	T v1;
	U v2;

	Symbol_Table(T _v1, U _v2) : v1{ _v1 }, v2{ _v2 } {}
	Symbol_Table() : v1{ T() }, v2{ U() }{}
};

template<typename T, typename U>
void print_vector(const vector<Symbol_Table<T,U>>& st)
// for testing
{
	for (int i = 0; i < st.size(); ++i) {
		cout << st[i].v1<<':'<<st[i].v2 << '\n';
	}
}

int main()
try {
	
	vector<Symbol_Table<int, string>> s_table{ {40, "John"},{41, "Smith"}, {43, "Arnold"}, {18, "Conner"} };
	print_vector(s_table);
}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}

