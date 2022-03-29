//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	12. Define a File_handle class with a constructor that takes a string argument
//	(the file name), opens the file in the constructor, and closes it in the
//	destructor.

//#include "std_lib_facilities.h"
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <fstream>

struct File_handle {
	File_handle(std::string name);
	~File_handle() { fs.close(); std::cout << "File closed!"; }

	void read_file(std::vector<std::string>& v);

	std::fstream fs;
};

File_handle::File_handle(std::string name) 
	: fs{ name }
{
	if (!fs) std::cerr<<"Can't open file";
	std::cout << "File opened!\n";
}

void File_handle::read_file(std::vector<std::string>& v)
{
	std::string s;
	while (fs >> s) {
		v.push_back(s);
	}
}

template <typename T>
void print_vector(const std::vector<T>& v)
{
	for (int i{}; i < v.size(); ++i) {
		std::cout << v[i];
		if (i < v.size() - 1) std::cout << ", ";
		if (i == v.size() - 1) std::cout << '\n';
	}
}

std::vector<std::string> v_file_input;

int main()
try {
	const std::string name{ "Text-file.txt" };
	File_handle file1{ name };
	file1.read_file(v_file_input);
	print_vector(v_file_input);
}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "unknown exception\n";
}

