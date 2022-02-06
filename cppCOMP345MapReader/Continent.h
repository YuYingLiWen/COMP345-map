#pragma once

#include <list>

#include "Territory.h"
#include "Country.h"

class Continent : public Territory
{
	static int _continent_index;
	
	std::string* _color_ptr;
	int* _army_value_ptr;
	std::list<Country*>* _countries_ptr; 

private:
	Continent() = delete; // Prevent accidental use 
	 
public:
	//Copy constructor. !!!Don't use unless really necessary - cause dupe index
	Continent(const Continent& to_copy);

	Continent(std::string& continent_name, int& army_value, std::string& color);
	~Continent();

	int get_army_value() const;
	std::string get_color() const;
	std::string to_string() const; 
	std::list<Country*>& get_countries() const;

	void add_country(Country& new_country);

	Continent& operator=(const Continent& continent);

	friend std::ostream& operator<<(std::ostream& stream, const Continent& continent);
};


