
#include <iostream>

struct Document;

//---------------------------------------PROBLEMATIC----------------------------------
struct IMachine {
	virtual void print(Document& doc) = 0;
	virtual void scan(Document& doc) = 0;
	virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine
{
	void print(Document& doc) override {
		//uses the print function
	}
	void scan(Document& doc) override {

	}
	void fax(Document& doc) override {

	}
};

struct Scanner : IMachine
{
	void print(Document& doc) override {

	}
	void scan(Document& doc) override {
		//uses the scan function
	}
	void fax(Document& doc) override {

	}
};
//	Need to break up IMachine into smaller interfaces
//	-	avoids providing the scanner interface to a printer if the printer is not also a scanner
//-----------------------------------------------------------------------------------------



struct IPrinter
{
	virtual void print(Document& doc) = 0;

};
struct IScanner
{
	virtual void scan(Document& doc) = 0;

};
struct IFax
{
	virtual void fax(Document& doc) = 0;

};



struct scanner : IScanner
{
	void scan(Document& doc) override {

	}
};

struct printer : IPrinter
{
	void print(Document& doc) override {

	}
};


struct IMachine : IPrinter, IScanner {};




//this way the person implementing your api can write the following...
struct Machine : IMachine
{
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

	void print(Document& doc) override {
		printer.print(doc);
	}
	void scan(Document& doc) override {
		scanner.scan(doc);
	}

};
// the person will have to implement the functionality of the functions listed in the interfaces
//		ie: define the functionality the devices they are programming for that are also IPrinter's and IScanner's
//			- They must follow the interfaces structure for everything to work correctly


int main(void) {

	return 0;
}