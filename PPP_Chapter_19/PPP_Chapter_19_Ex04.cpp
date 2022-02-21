//	PPP_Chapter_19.cpp
// 
//	Exercise solutions from the book:
//	************************************************************************************
//	* Programming Principles and Practice Using C++, Second Edition, Bjarne Stroustrup *
//	************************************************************************************
//	4. Modify class Link from §17.9.3 to be a template with the type of value
//	as the template argument.Then redo exercise 13 from Chapter 17 with
//	Link<God>.

#include "std_lib_facilities.h"

struct God {
	God(const string& n, const string& m, const string& v, const string& w)
		: name{ n }, mythology{ m }, vehicle{ v }, weapon{ w } { }

	string name;
	string mythology;
	string vehicle;
	string weapon;
};

ostream& operator<<(ostream& os, const God& g)
{
	return os << '-' << g.name << ',' << g.mythology
		<< ',' << g.vehicle << ',' << g.weapon;
}

bool operator<(const God& a, const God& b) { return a.name < b.name; }
bool operator>(const God& a, const God& b) { return a.name > b.name; }
bool operator==(const God& a, const God& b) { return a.name == b.name; }
bool operator<=(const God& a, const God& b) { return a.name <= b.name; }
bool operator>=(const God& a, const God& b) { return a.name >= b.name; }
bool operator!=(const God& a, const God& b) { return a.name != b.name; }

template<typename T>
class Link {
public:
	Link(const T& v, Link<T>* p = nullptr, Link<T>* s = nullptr)
		: value{ v }, prev{ p }, succ{ s } { }

	T value;

	Link<T>* insert(Link<T>* n); // insert n before this object
	Link<T>* add(Link<T>* n); // insert n after this object
	Link<T>* erase(); // remove this object from list
	const Link<T>* find(const T& s) const; // find s in const list (see §18.5.1)

	Link<T>* advance(int n) const; // move n positions in list
	Link<T>* add_ordered(Link<T>* n);	// order in lexicographical order

	Link<T>* next() const { return succ; }
	Link<T>* previous() const { return prev; }

private:
	Link<T>* prev;
	Link<T>* succ;
};

template<typename T>
Link<T>* Link<T>::insert(Link<T>* n) // insert n before this object; return n
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this; // this object comes after n
	if (prev) prev->succ = n;
	n->prev = prev; // this object’s predecessor becomes n’s predecessor
	prev = n; // n becomes this object’s predecessor
	return n;
}

template<typename T>
Link<T>* Link<T>::add(Link<T>* n) // insert n after p; return n
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->prev = this; // this object comes before n
	if (succ) succ->prev = n;
	n->succ = succ;	//this objects successor becomes n's successor
	succ = n;
	return n;
}

template<typename T>
Link<T>* Link<T>::erase() // remove *p from list; return p’s successor
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

template<typename T>
Link<T>* Link<T>::advance(int n) const // move n positions in list
// return nullptr for “not found”
// positive n moves forward, negative backward
{
	Link<T>* p = const_cast<Link<T>*>(this);
	if (this == nullptr) return nullptr;
	if (0 < n) {
		while (n--) {
			if (succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if (n < 0) {
		while (n++) {
			if (p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}

template<typename T>
Link<T>* Link<T>::add_ordered(Link<T>* n)
{
	Link<T>* p = this;

	while (p) {

		if (n->value < p->value) {			// if n is smaller than this(p)
			if (p->prev == nullptr) {				// if this(p) is 1st link
				p = p->insert(n);
				return p;
			}
			else p = p->advance(-1);
		}
		else if (p->value < n->value) {		// if n is larger than this(p)
			if (p->succ == nullptr) {
				p = p->add(n);
				return p;
			}
			else if (n->value < p->succ->value) {
				p = p->add(n);
				return p;
			}
			else p = p->advance(1);
		}
	}
}

//----------------------------------------------------------------------------
// functions for God type

Link<God>* find_god(Link<God>* p, const string& s) // find s in list;
// return nullptr for “not found”
{
	Link<God>* temp = p;
	while (temp) {
		if (temp->value.name == s) return temp;
		temp = temp->next();
	}
	return nullptr;
}

void lexicograph_order(Link<God>* in, Link<God>* out)
{
	while (in) {	// go back to 1st Link
		if (!in->previous()) break;
		in = in->previous();
	}

	string myth = out->value.mythology;	//which mythology to search for?

	while (in) {
		if (in->value.mythology == myth) {	// extract only gods from specified mythology
			Link<God>* s = find_god(out, in->value.name);
			if (s == nullptr) {
				Link<God>* p = in;				// copy link to temp
				in = in->erase();			// delete link from original list
				out = out->add_ordered(p);	// add the link from temp
			}
			else if (s->value.name == in->value.name) {
				cout << in->value.name << " already entered." << '\n';
			}
		}
		else in = in->next();				// keep going through the list
	}
}

void print_all(Link<God>* p)
{
	while (p) {
		if (!p->previous()) break;
		p = p->previous();
	}

	if (p->value.mythology == "Norse") cout << "Norse gods:\n";
	else if (p->value.mythology == "Roman") cout << "Roman gods:\n";
	else if (p->value.mythology == "Greek") cout << "Greek gods:\n";
	else {}

	while (p) {
		cout << '-' << p->value.name << ',' << p->value.mythology
			<< ',' << p->value.vehicle << ',' << p->value.weapon;
		if (p = p->next()) cout << '\n';
	}
}

int main()
try {	
	Link<God>* gods = new Link<God>{ { "Hades ","Greek","","The Helm of Darkness"} };
	gods = gods->add(new Link<God>{ { "Poseidon ","Greek","The Chariot of the Sea","The Trident of Poseidon"} });
	gods = gods->add(new Link<God>{ { "Saturn ","Roman","","Scythe" } });
	gods = gods->add(new Link<God>{ { "Aphrodite","Greek","","Cestus " } });
	gods = gods->add(new Link<God>{ { "Odin","Norse","Eight-legged flying horse, Sleipnir","Gungnir the spear" } });
	gods = gods->add(new Link<God>{ { "Freya ","Norse","cats of Freya","Dainsleif (sword)" } });
	gods = gods->add(new Link<God>{ { "Jupiter ","Roman","","Lightning Bolt" } });
	gods = gods->add(new Link<God>{ { "Heimdall","Norse","","Gjallarhorn the Yelling Horn" } });
	gods = gods->add(new Link<God>{ { "Vidar","Norse","","Vidar's Shoes" } });
	gods = gods->add(new Link<God>{ { "Ullr ","Norse","","Arrow" } });
	gods = gods->add(new Link<God>{ { "Athena","Greek","","The Aegis" } });
	gods = gods->add(new Link<God>{ { "Juno","Roman","Cart","Spear" } });
	gods = gods->add(new Link<God>{ { "Minerva","Roman","","Spear" } });
	gods = gods->add(new Link<God>{ { "Mars","Roman","","Spear"} });


	//print_all(gods);

	Link<God>* norse_gods = new Link<God>{ { "Thor","Norse","Chariot of Thunder","Hammer" } };
	Link<God>* greek_gods = new Link<God>{ { "Zeus ","Greek","","Thunderbolts" } };
	Link<God>* roman_gods = new Link<God>{ { "Apollo","Roman","Sun Chariot","Silver Bow and Arrow" } };

	lexicograph_order(gods, greek_gods);
	lexicograph_order(gods, norse_gods);
	lexicograph_order(gods, roman_gods);

	print_all(greek_gods);
	cout << '\n';
	print_all(norse_gods);
	cout << '\n';
	print_all(roman_gods);
	cout << '\n';

	return 0;
}

catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
}
catch (...) {
	cerr << "unknown exception\n";
}

