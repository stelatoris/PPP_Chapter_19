//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	8. Implement an allocator(§19.3.7) using the basic allocation functions malloc()
//	and free() (§B.11.4).Get vector as defined by the end of §19.4 to
//	work for a few simple test cases.Hint: Look up “placement new”and
//	“explicit call of destructor” in a complete C++ reference.

//#include "std_lib_facilities.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class allocator {
public:
	T* allocate(int n) { return malloc(n*sizeof(T)); }
	void deallocate(T* p) { free(p); }

	void construct(T* p, const T& v) { new (p) T(v); }	// std::allocator::construct
	void destroy(T* p) { p->~T(); }						// std::allocator::destroy
};


// an almost real vector of Ts:
template<typename T, typename A=allocator<T>>
class vector { // read “for all types T” (just like in math)
	A alloc;	// use allocate to handle memory for elements
	int sz; // the size
	T* elem; // a pointer to the elements
	int space; // size + free space
public:
	vector() : sz{ 0 }, elem{ nullptr }, space{ 0 } { }
	explicit vector(int s) :sz{ s }, elem{ new T[s] }, space{ s }
	{
		for (int i = 0; i < sz; ++i) elem[i] = 0; // elements are initialized
	}
	vector(const vector&); // copy constructor
	vector& operator=(const vector&); // copy assignment
	vector(vector&&); // move constructor
	vector& operator=(vector&&); // move assignment
	~vector() { delete[] elem; } // destructor
	T& operator[] (int n) { return elem[n]; } // access: return reference
	const T& operator[] (int n) const { return elem[n]; }
	int size() const { return sz; } // the current size
	int capacity() const { return space; }
	void resize(int newsize); // growth
	void push_back(const T& d);
	void reserve(int newalloc);
};

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a)
{
	if (this == &a) return *this; // self-assignment, no work needed
	if (a.sz <= space) { // enough space, no need for new allocation
		for (int i = 0; i < a.sz; ++i) elem[i] = a.elem[i]; // copy elements
		sz = a.sz;
		return *this;
	}
	T* p = new T[a.sz]; // allocate new space
	for (int i = 0; i < a.sz; ++i) p[i] = a.elem[i]; // copy elements
	delete[] elem; // deallocate old space
	space = sz = a.sz; // set new size
	elem = p; // set new elements
	return *this; // return a self-reference
}

template<typename T, typename A>
vector<T,A>::vector(vector&& a)
	:sz{ a.sz }, elem{ a.elem } // copy a’s elem and sz
{
	a.sz = 0; // make a the empty vector
	a.elem = nullptr;
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector&& a) // move a to this vector
{
	delete[] elem; // deallocate old space
	elem = a.elem; // copy a’s elem and sz
	sz = a.sz;
	a.elem = nullptr; // make a the empty vector
	a.sz = 0;
	return *this; // return a self-reference (see §17.10)
}

template<typename T, typename A>
void vector<T,A>::reserve(int newalloc)
{
	if (newalloc <= space) return; // never decrease allocation
	T* p = new T[newalloc]; // allocate new space
	for (int i = 0; i < sz; ++i) p[i] = elem[i]; // copy old elements
	delete[] elem; // deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T, typename A>
void vector<T,A>::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) elem[i] = 0; // initialize new elements
	sz = newsize;
}

template<typename T, typename A>
void vector<T,A>::push_back(const T& d)
// increase vector size by one; initialize the new element with d
{
	if (space == 0)
		reserve(8); // start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); // get more space
	elem[sz] = d; // add d at end
	++sz; // increase the size (sz is the number of elements)
}

template<typename T>
void print_vector(vector<T>& v)
{
	for (int i = 0; i < v.size(); ++i) {		
		std::cout << v[i];
		if (i < v.size()-1)std::cout << ',';
	}
	std::cout << '\n';
}

int main()
try {
	vector<int>v_int1;
	v_int1.push_back(1);
	v_int1.push_back(2);
	v_int1.push_back(3);
	v_int1.push_back(4);
	v_int1.push_back(5);

	vector<int>v2;
	v2 = v_int1;
	v2.push_back(6);
	//vector<int>v3{ v2 };

	print_vector(v_int1);
	print_vector(v2);

	

}

catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
}
catch (...) {
	std::cerr << "unknown exception\n";
}

