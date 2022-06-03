#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

using namespace std;

//The way the are now:
//-------------------------------------------------------------------------

//just a utility class for modeling a html element in an OOP way
class HtmlElement
{
	friend class HtmlBuilder;
	string name, text;
	vector<HtmlElement> elements;
	const size_t indent_size = 2;

	HtmlElement() {}
	HtmlElement(const string& name, const string& text) : name(name), text(text) {}

public:
	string str(int indent = 0) const {
	ostringstream oss;
	string i(indent_size * indent, ' ');
	oss << i << "<" << name << ">" << endl;
	if (text.size() > 0)
		oss << string(indent_size * (indent + 1), ' ') << text << endl;

	for (const auto& e : elements)
		oss << e.str(indent + 1);

	oss << i << "</" << name << ">" << endl;
	return oss.str();

	}

	static HtmlBuilder create(string root_name) {
		return { root_name };
	}
};

//Builder Pattern

class HtmlBuilder
{
	HtmlElement root;
public:
	HtmlBuilder(string root_name)
	{
		root.name = root_name;
	}

	//changed void to HtmlBuilder& so that the 'fluent interface' could be implemented through use of call chains in main
	HtmlBuilder& add_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return *this;
	}

	HtmlElement build() {
		return root;
	}

	string str() const {
		return root.str();
	}

	operator HtmlElement() const {
		return root;
	}
};


int main(void) {

	//The way things used to be:
	// ------------------------------------------------------------------------
	// 
	// 
	//something being put together. in this case a string of words inside of html tags
	auto text = "hello";
	string output;
	output += "<p>";
	output += text;
	output += "</p>";
	cout << output << endl;

	//Does the same thing in a slightly smarter way
	//more expandable
	string words[] = { "hello", "world" };
	ostringstream oss;
	oss << "<ul>";
	for (auto w : words) {
		oss << "       <li>" << w << "</li>";
	}
	oss << "</ul>";
	cout << oss.str() << endl;
	//--------------------------------------------------------------------------
	//the way they are now:

	HtmlBuilder builder{ "ul" };

	//before use of fluent interface...
	builder.add_child("li", "hello");
	builder.add_child("li", "world");

	//using fluent interface....common in builder design pattern
	//changing the add_child function return type from void to HtmlBuilder& allows call chaining.
	builder.add_child("li", "hello").add_child("li", "world");

	cout << builder.str() << endl;

	HtmlElement elem = HtmlElement::create("ul").add_child("", "");

	HtmlElement::create("ul").add_child("", "").build();

	return 0;
}