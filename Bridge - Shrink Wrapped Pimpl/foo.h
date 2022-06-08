#pragma once
#include "pimpl.h"

class Foo
{
	class impl;
	pimpl<impl> impl;

	//then define the 'impl' class in the foo.cpp file. 
	//and write members of this class that call function of the nested class 
	//this way the class implementation can be hidden in .cpp files and never exposed to the user of the API
};

