#include <iostream>
#include <string>
#include <functional>

using namespace std;

struct Logger
{
	function<void()> func;
	string name;

	Logger(const function<void()>& func, const string& name) : func(func), name(name) {}

	void operator()() const
	{
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}
};

template<typename Func>
struct Logger2
{
	Func func;
	string name;

	Logger2(const Func& func, const string& name) : func(func), name(name) {}

	void operator()() const
	{
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}
};

template <typename Func> auto make_logger2(Func func, const string& name)
{
	return Logger2<Func>{ func, name};
}

int main(void)
{
	Logger([]() {cout << "Hello" << endl; }, "HelloFunction")();

	auto log = make_logger2([]() {cout << "Hello" << endl; }, "HelloFunction");
	log();

	return 0;
}