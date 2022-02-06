#include "Continent.h"

int Continent::_continent_index = 0;

Continent::Continent(const Continent& to_copy) : Territory(*new int(to_copy.get_index()), *new std::string(to_copy.get_name())) {
	_army_value_ptr = new int(to_copy.get_army_value());
	_color_ptr = new std::string(to_copy.get_color());
	_countries_ptr = &copy(to_copy.get_countries());
}


Continent::Continent(std::string& continent_name, int& army_value, std::string& color) : Territory(*(new int(++_continent_index)), continent_name) {

	_army_value_ptr = &army_value;
	_color_ptr = &color;
	_countries_ptr = new std::list<Country*>();
}

int Continent::get_army_value() const{
	return *_army_value_ptr;
}

std::string Continent::to_string() const{

	std::string tmp = "";

	for (Country* c : get_countries()) tmp += "   " + c->to_string() + "\n";

	return Territory::to_string() + " | Army: " + std::to_string(get_army_value()) + " | " + get_color() + "\n"
		+ tmp;
}

void Continent::add_country(Country& new_country) {
	get_countries().push_back(&new_country);
}

Continent& Continent::operator=(const Continent& continent) 
{
	delete _color_ptr;
	delete _army_value_ptr;
	delete _countries_ptr;
	delete& get_name();
	delete& get_index();

	_army_value_ptr = new int(continent.get_army_value());
	_color_ptr = new std::string(continent.get_color());
	_countries_ptr = &copy(continent.get_countries());

	set_index(*new int(continent.get_index()));
	set_name(*new std::string(continent.get_name()));
	
	return *this;
}


std::list<Country*>& Continent::get_countries() const{
	return *_countries_ptr;
}

std::string Continent::get_color() const{
	return *_color_ptr;
}

Continent::~Continent() {
	std::cout << "Unloaded:\t" << typeid(Continent).name() << "\t\t" << Territory::get_name() << std::endl;

	_continent_index = 0;

	delete _color_ptr;
	delete _army_value_ptr;
	delete _countries_ptr;
}

std::ostream& operator<<(std::ostream& stream, const Continent& continent) {

	stream << continent.to_string();

	return stream;
}