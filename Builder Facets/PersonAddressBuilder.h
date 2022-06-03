#pragma once
#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase
{
	typedef PersonAddressBuilder Self;
public:
	PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

	Self& at(std::string street_address)
	{
		person.street_address = street_address;
		return *this;
	}

	Self& with_PostCode(std::string post_Code)
	{
		person.post_code = post_Code;
		return *this;
	}

	Self& in(std::string city)
	{
		person.city = city;
		return *this;
	}

};

