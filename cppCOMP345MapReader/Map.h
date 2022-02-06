#pragma once


#include <queue>
#include <vector>
#include "Continent.h"

class Map
{
	static Map *_instance;
	std::list<Continent*>* _continents_ptr;
	std::vector<Country*>* _countries_ptr;
	
private:
	Map();

	//Copy constructor. !!!Don't use unless really necessary
	Map(const Map& to_copy);
	bool help_validate(std::queue<Country*>& visited_countries, int& size, int& count);

public:
	~Map();

	static Map* get_instance();

	// Checks if loaded map is valid; return: valid=true; invalid=false;
	bool validate(); 

	void display() const; // Displays the Map obj
	void set_continent(Continent& new_continent); // Add a new continent
	void set_country(int& continent_index, Country& new_country); // Add a new country
	void set_border(std::vector<std::string> splited_borders); // Add a new neighbor to a country
	Country* get_country(int index); // Get a country by index
	std::vector<Country*>& get_countries() const; // Get all countries
	std::list<Continent*>& get_continents() const; // Get all continents

	void unload(); // Clears all data on instance

	Map& operator=(const Map& country);

	friend std::ostream& operator<<(std::ostream& stream, Map& map); // Stream insertion 
};
