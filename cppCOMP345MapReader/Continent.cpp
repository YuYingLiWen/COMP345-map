#include "Continent.h"

int Continent::_continent_index = 0;

Continent::Continent(std::string& continent_name, int& army_value, std::string& color) : Territory(*(new int(++_continent_index)), continent_name) {

	_army_value_ptr = &army_value;
	_color_ptr = &color;
	_countries = new std::list<Country*>();
}

int Continent::get_index() {
	return Territory::get_index();
}

int Continent::get_army_value() {
	return *_army_value_ptr;
}

std::string Continent::to_string() {

	std::string tmp = "";

	for (Country* c : get_countries()) tmp += "   " + c->to_string() + "\n";

	return Territory::to_string() + " | Army: " + std::to_string(get_army_value()) + " | " + get_color() + "\n"
		+ tmp;
}

void Continent::add_country(Country& new_country) {
	get_countries().push_back(&new_country);
}


std::list<Country*>& Continent::get_countries() {
	return *_countries;
}

std::string Continent::get_color() {
	return *_color_ptr;
}


Continent::~Continent() {
	std::cout << "Unloaded:\t" << typeid(Continent).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _color_ptr;
	delete _army_value_ptr;
	delete _countries;
}