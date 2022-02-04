#pragma once

#include <iostream>
#include <list>

#include "Territory.h"
#include "Country.h"

class Continent : public Territory
{
	static int _continent_index;
	
	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Country*>* _countries; 

private:
	Continent() = delete;

public:
	
	Continent(std::string& continent_name, int& army_value, std::string& color);
	~Continent();

	int get_index();
	int get_army_value();
	std::string get_color();
	std::string to_string(); // Display obj as string
	std::list<Country*>& get_countries();

	void add_country(Country& new_country);
};

