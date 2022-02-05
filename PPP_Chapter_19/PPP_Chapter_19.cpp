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
//  For both inputand output use a{ val, val, val } format.That will allow
//  read_val() to also handle the S<vector<int>> variable.
//  Remember to test after each step.

#include "std_lib_facilities.h"

template<typename T> 
struct S {
    
    S(T v) : val{ v } {}        // Drill 2
    T& get();                   // Drill 5

    T val;
};

//Drill 6
template<typename T> T& S<T>::get()
{
    return val;
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
    cout <<"s_int: " << s_int.val << '\n';
    cout << "s_char: " << s_char.val << '\n';
    cout << "s_dbl: " << s_dbl.val << '\n';
    cout << "s_string: " << s_string.val << '\n';
    cout << "vector s_vec: ";
    for (int i = 0; i < s_vec.val.size(); ++i) {
        cout << s_vec.val[i];
        if (i < s_vec.val.size() - 1) cout << ',';
    }




}

