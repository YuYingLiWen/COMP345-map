#pragma once

#include <list>
#include "Territory.h"

class Country : public Territory
{
private:
	Country() = delete;

	std::list<Country*>* _neighbor_countries;
	bool* _visited_ptr; // Used for Map's validation check
	int* _army;

public:
	
	Country(int& index, std::string& country_name);
	~Country();

	std::list<Country*>& get_neighbors(); // Returns a reference to the list of neighbors
	void set_neighbor(Country& bordered_country); // Add a new neighbor 
	bool& get_visited(); // Check is visited
	void set_visited(bool& visited); // Set visited
	int& get_army();
	void set_army(int& army);
	std::string to_string(); // Display obj as string
};

