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
class Pair {
	T v1;
	U v2;
public:
	Pair(T _v1, U _v2): v1{_v1}, v2{_v2}{}
	Pair() : v1{T()}, v2{U()} {}
	T val1() const { return v1; }
	U val2() const { return v2; }
};

template<typename T, typename U>
class Symbol_Table {
	vector< Pair<T,U>> table;
public:
	Symbol_Table() {}
	int size() const { return table.size(); }
	void add_symbol(const T& t, const U& u) { table.push_back({ t,u }); }
	vector< Pair<T, U>> get_table() const { return table; }
	U operator[](const T& v);
	const U operator[](const T& v) const;
};

template<typename T, typename U>
U Symbol_Table<T, U>::operator[](const T& v)
{
	for (auto& a : table)
		if (a.val1() == v)
			return a.val2();
}

template<typename T, typename U>
const U Symbol_Table<T, U>::operator[](const T& v) const
{
	for (auto& a : table)
		if (a.val1() == v)
			return a.val2();
}

template<typename T, typename U>
void print_vector(const Symbol_Table<T, U>& st)
// for testing
{
	for (int i = 0; i < st.size(); ++i) {
		cout << st.get_table()[i].val1()
			<<','
			<< st.get_table()[i].val2()<< '\n';
	}
}

void create_ascii_vector(Symbol_Table<char, int>& v)
{
	for (int i = 32; i < 127; ++i) {
		v.add_symbol(char(i), i);
	}
}

int main()
try {	
	Symbol_Table<string,double> st;
	st.add_symbol("PI", 3.14159'26535'89793'23846);
	st.add_symbol("Phi", 1.61803'39887'49894'84820);
	st.add_symbol("Omega", 0.56714'32904'09783'87299);
	st.add_symbol("c", 299'792'458);	

	//vector<Symbol_Table<int, string>> s_table{ {40, "John"},{41, "Smith"}, {43, "Arnold"}, {18, "Conner"} };
	//print_vector(st);

	cout <<"PI:"<< st["PI"] << '\n';
	cout << "Phi: " << st["Phi"] << '\n';
	cout << "c: " << st["c"] << '\n';
	cout << "Omega: " << st["Omega"] << '\n';

	cout << "-------------------------------------------\n";
	// Created an ASCII table for fun
	Symbol_Table<char, int> ascii;
	create_ascii_vector(ascii);
	print_vector(ascii);
}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}

