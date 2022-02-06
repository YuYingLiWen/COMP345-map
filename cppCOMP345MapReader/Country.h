#pragma once

#include <list>
#include "Territory.h"
#include "Player.h"

class Country : public Territory
{
private:
	Country() = delete; //Prevents wrong call

	std::list<Country*>* _neighbor_countries_ptr;
	bool* _visited_ptr; // Used for Map's validation check
	int* _stationed_army_ptr;
	Player* _player_ptr;

public:

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Country(const Country&  to_copy);


	Country(int& index, std::string& country_name);
	~Country();

	std::list<Country*>& get_neighbors() const; // Returns a reference to the list of neighbors
	void set_neighbor(Country& bordered_country); // Add a new neighbor 

	// Claim a country
	void claim(Player& player);

	// Check who owns the country. returns player or null
	Player* check_claim() const;


	// Check is visited
	bool& get_visited() const; 
	void set_visited(bool& visited); 
	int& get_stationed_army() const;
	void set_stationed_army(int& army);
	std::string to_string(); 

	Country& operator=(const Country& country); 

	friend std::ostream& operator<<(std::ostream& stream, Country& country); 
};

