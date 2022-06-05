#define _USE_MATH_DEFINES

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>


using namespace std;
struct Address
{
	string street, city;
	int suite;

	Address(const string& street, const string& city, int suite) : street(street), city(city), suite(suite) {}
	Address(Address& address) : street(address.street), city(address.city), suite(address.suite) {}

	friend ostream& operator<< (ostream& os, Address& address)
	{
		os << "street: " << address.street << " city: " << address.city << " suite: " << address.suite << endl;
		return os;
	}

};


struct Contact
{
	string name;
	Address *address;

	Contact(const string& name, Address* address) : name(name), address(address) {}

	Contact(const Contact& other) : name{ other.name }, address{ new Address {*other.address} } {}

	friend ostream& operator<< (ostream& os, Contact& contact)
	{
		os << "name: " << contact.name << endl;
		os << *contact.address;
		return os;
	}
};


int main()
{

	Contact john("John Doe", new Address{ "123 East Dr", "London", 123 });
	//Contact jane("Jane Smith", Address{ "123 East Dr", "London", 103 });

	//instead of constructing all these tenants that live at the same address each time with only a different Unit Number....
	//Can create a PROTOTYPE that contains the same address and creates tenants of different suite numbers

	//this is sort of prototyping John to create Jane
	//Contact jane = john;//Shallow copy

	Contact jane(john); // --- Deep Copy
	jane.address->suite = 103;
	jane.name = "Jane Smith";

	cout << john << endl << jane << endl;

	return 0;


}