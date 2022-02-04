#pragma once

#include <string>
#include <iostream> // To be removed

class Territory
{

private:
	int* _index_ptr;
	std::string* _name_ptr;
	//Player* player;

public:
	Territory() = delete;
	Territory(int& index, std::string& territory_name);
	~Territory();

	std::string to_string(); // Display obj as string

	//void claim(Player& player);
	//Player* check_claim();

	std::string get_name() const;
	int get_index() const;
};

