//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//  Drill
//  1. Define template<typename T> struct S { T val; }; .
//  2. Add a constructor, so that you can initialize with a T.
//  3. Define variables of types S<int>, S<char>, S<double>, S<string>, and
//     S<vector<int>>; initialize them with values of your choice.
//  4. Read those values and print them.
//  5. Add a function template get() that returns a reference to val.
//  6. Put the definition of get() outside the class.
//  7. Make val private.
//  8. Do 4 again using get().
//  9. Add a set() function template so that you can change val.
//  10. Replace set() with an S<T>::operator=(const T&).Hint : Much simpler
//  than §19.2.5.
//  11. Provide constand non - const versions of get().
//  12. Define a function template<typename T> read_val(T & v) that reads from
//  cin into v.
//  13. Use read_val() to read into each of the variables from 3 except the
//  S<vector<int>> variable.
//  14. Bonus: Define input and output operators(>> and << ) for vector<T>s.
//  For both input and output use a{ val, val, val } format.That will allow
//  read_val() to also handle the S<vector<int>> variable.
//  Remember to test after each step.

#include "std_lib_facilities.h"

template<typename T> 
struct S {
    S() : val{ T() } {}
    S(T v) : val{ v } {}        // Drill 2
    T& get();                   // Drill 5
    const T& get() const;       // Drill 11
    void set(const T& v);
    T& operator=(const T&);     // Drill 10
private:                        // Drill 7
    T val;
};

//Drill 6
template<typename T> T& S<T>::get() { return val; }

template<typename T> const T& S<T>::get() const { return val; }

// Drill 9
template<typename T> void S<T>::set(const T& v) { val = v; }

// Drill 13
template<typename T> T& S<T>::operator=(const T& t)
{    
    val = t;
    return val;
}

template<typename T> istream& operator>>(istream& is, S<T>& my_s)
{
    T v;
    is >> v;
    if (!is) return is;
    my_s = v;
    return is;
}

  //14. Bonus: Define input and output operators(>> and << ) for vector<T>s.
  //For both input and output use a{ val, val, val } format.That will allow
  //read_val() to also handle the S<vector<int>> variable.
  //Remember to test after each step.
 
template<typename T> istream& operator>>(istream& is, vector<T>& v)
{
    char ch1{' '};
    T val;

    if (is >> val >> ch1 && ch1 == ',') {
        v.push_back(val);
    }

    return is;
}

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "{ ";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i < v.size() - 1) os << ", ";
    }
    os << " }";
    return os;
}

template<typename T> void read_val(T& v)
{
    cin >> v;
}

int main()
{
    // Drill 3
    S<int> s_int{ 5 };
    S<char> s_char{ 'x' };
    S<double>s_dbl{ 3.14 };
    S<string>s_string{ "Hello, world" };
    S < vector<int>> s_vec{ vector < int>{1,2,3,4} };

    // Drill4
    // Drill 8
    /*cout <<"s_int: " << s_int.get() << '\n';
    cout << "s_char: " << s_char.get() << '\n';
    cout << "s_dbl: " << s_dbl.get() << '\n';
    cout << "s_string: " << s_string.get() << '\n';
    cout << "vector s_vec: ";
    for (int i = 0; i < s_vec.get().size(); ++i) {
        cout << s_vec.get()[i];
        if (i < s_vec.get().size() - 1) cout << ',';
    }*/

    /*
    S<double>s_dbl2= s_dbl;
    cout << "\ns_dbl2: " << s_dbl2.get() << '\n';

    // Drill 13
    cout << "Input an int: ";
    read_val(s_int);
    cout << "s_int() read: " << s_int.get() << '\n';

    cout << "Input a char: ";
    read_val(s_char);
    cout << "s_char() read: " << s_char.get() << '\n';

    cout << "Input a double: ";
    read_val(s_dbl);
    cout << "s_dbl() read: " << s_dbl.get() << '\n';

    cout << "Input a string: ";
    read_val(s_string);
    cout << "s_string() read: " << s_string.get() << '\n';
    */

    cout <<'\n' << s_vec.get()<<'\n';

    S < vector<int>> s_vec2;
    cout << "Please enter a vector in v,v,v,v etc format:" << '\n';
    read_val(s_vec2);

    cout << s_vec2.get() << '\n';
}

