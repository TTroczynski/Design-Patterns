#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>

#include "headers.h"

struct Printer
{
	//Monostate Design Pattern
	// - not recommended for use in production code.
	// - allows multiple instances to be created
	// - doesnt communicate that it is a singleton by providing static functions and hiding all else
	//		thereby forcing the user to use it properly or have them realize this class is a singleton
	// 
	//there is a single static variable that would exist for all Printers.
	//the getter would always return what the last set method call set it to, otherwise all instances would 
	//receive the value it was constructed with.
	//So you cant have more than one printer.
	//AKA singleton

	//Problem is that it doesnt immediately appear to be a singleton
	//users of this code would likely create multiple instances and wonder why all instances have the same id

	static int id;
public:
	int get_id() const { return id; }
	void set_id(int id) const { this->id = id; }

};

int main() {

	Printer p;
	int id = p.get_id();

	Printer p2;
}