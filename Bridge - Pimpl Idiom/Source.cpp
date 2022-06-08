#include "Person.h"

int main(void)
{
	Person p;
	p.name = "Tom";//i know this is not the right way of setting this..

	p.greet(); //Point is that we can see that greet calls the nested class' greet method
	//			meaning that the implementation details of a class can be completely hidden from the 
	//			user of the API since the cpp files dont ship with the library
	//			the customer can see the Person class but they cant see the implementation details of the PersonImpl class
	//			The PersonImpl class is hidden in the cpp file.
}