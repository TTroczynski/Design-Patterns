#pragma once
#include <string>
#include <iostream>

class PersonBuilder;

class Person
{
	//address
	std::string street_address, post_code, city;

	//employment
	std::string company_name, position;
	int annual_income{ 0 };

	Person()
	{
		std::cout << "Person created\n";
	}

public:
	~Person()
	{
		std::cout << "Person destroyed.\n";
	}

	static PersonBuilder create();

	Person(Person&& other) : street_address{move(other.street_address)}, post_code{move(other.post_code)},
		city{move(other.city)}, company_name{move(other.company_name)}, position{other.position},
		annual_income{ other.annual_income } {}

	Person& operator= (Person&& other)
	{
		if (this == &other)
			return *this;
		street_address = move(other.street_address);
		post_code = move(other.post_code);
		city = move(other.city);
		company_name = move(other.position);
		position = move(other.position);
		annual_income = other.annual_income;
		return *this;
	}


	friend std::ostream& operator<<(std::ostream& os, const Person& person) {
		
		os << "street address: " << person.street_address 
			<< " post_code: " << person.post_code 
			<< " city: " << person.city 
			<< " company_name: " << person.company_name 
			<< " position: " << person.position
			<< " annual_income: " << person.annual_income;
		return os;
	}


	friend class PersonBuilder;
	friend class PersonJobBuilder;
	friend class PersonAddressBuilder;
};

