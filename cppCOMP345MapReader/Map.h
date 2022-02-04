#pragma once


#include <queue>
#include <vector>
#include "Continent.h"

class Map
{
	static Map *_instance;
	std::list<Continent*>* _continents;
	std::vector<Country*>* _countries;
	
private:
	Map();
	bool help_validate(std::queue<Country*>& visited_countries, int& size, int& count);


public:
	~Map();

	static Map *get_instance();
	bool validate(); // Checks if loaded map is valid
	void display(); // Displays the Map obj
	void set_continent(Continent& new_continent); // Add a new continent
	void set_country(int& continent_index, Country& new_country); // Add a new country
	void set_border(std::vector<std::string> splited_borders); // Add a new neighbor to a country
	Country* get_country(int index); // Get a country by index
	std::vector<Country*>& get_countries(); // Get all countries
	std::list<Continent*>& get_continents(); // Get all continents

	void unload(); // Clears all data on instance
};
