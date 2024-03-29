#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

using namespace std;

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main()
{

	Person p = Person::create()
		.lives()
			.at("123 London Road")
			.with_PostCode("SW1 1GB")
			.in("London")
		.works()
			.at("PragmaSoft")
			.as_a("Consultant")
			.earning(10e6);
	cout << p << endl;
	return 0;
}