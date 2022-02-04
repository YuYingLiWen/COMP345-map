#include "Map.h"

Map* Map::_instance = nullptr;

Map::Map() {
	_continents = new std::list<Continent*>();
	_countries = new std::vector<Country*>();
}

Map* Map::get_instance() {
	if (_instance == nullptr) {
		_instance = new Map();
	}
	return _instance;
}

void Map::set_continent(Continent& new_continent) {

	_continents->push_back(&new_continent);
}

void Map::set_country(int& continent_index, Country& new_country) {

	try {
		bool found = false;

		for (Continent* continent : get_continents()) {
			if (continent_index == continent->get_index()) {
				found = true;
				get_countries().push_back(&new_country);
				continent->add_country(new_country);
			}
		}
		if (!found) throw std::runtime_error(" Fail to find continent: " + continent_index);
	}
	catch (std::runtime_error e) {
		throw e;
	}
}

void Map::set_border(std::vector<std::string> splited_borders) {

	try {
		int curr_country_index = stoi(splited_borders[0]) - 1;

		for (size_t i = 1; i < splited_borders.size(); i++) { // 0 is the current selected country the remainig are its neighbours

			Country* country = get_country(stoi(splited_borders[i]));

			if (country) {
				get_countries()[curr_country_index]->set_neighbor(*country);
			}
			else {
				throw new std::runtime_error("Country not found for " + (curr_country_index + 1));
			}
		}
	}
	catch(std::runtime_error e) {
		throw e;
	}
}

bool Map::validate() {

	std::queue<Country*> queue;

	queue.push(get_countries()[0]);

	get_countries()[0]->set_visited(*new bool(true));

	int size = get_countries().size();
	int count = 0;

	return help_validate(queue, size, count);
}

bool Map::help_validate(std::queue<Country*>& to_be_visited, int& size, int& count) {
	
	if (to_be_visited.size() <= 0) {
		std::cout << "\n-- MAP VALIDATION PASS: " << count << std::endl;

		if (size == count) return true;
		return false;
	}
	else {

		Country* current = to_be_visited.front();
		to_be_visited.pop();
		
		std::list<Country*>& neighbors = current->get_neighbors();

		if (neighbors.size() <= 0) { // Dead end
			std::cout << "-- MAP FAIL VALIDATION: DEAD END --" << std::endl;
			return false;
		}
		else {
			for (Country* neighbor : neighbors) {

				if (!neighbor->get_visited()) {
					neighbor->set_visited(*new bool(true));

					to_be_visited.push(neighbor);
				}
			}
		}
	}

	return help_validate(to_be_visited, size, ++count);
}

void Map::display() {

	if (_continents->size() == 0 && _countries->size() == 0) return;

	std::cout << "-- DISPLAY --\n" << std::endl;

	for (Continent* continent : *_continents) {
		std::cout << continent->to_string() << std::endl;
	}

	std::cout << "-- DISPLAY END --\n" << std::endl;

}

Country* Map::get_country(int index) {
	for (Country* c : get_countries()) {
		if (c->get_index() == index) return c;
	}

	return nullptr;
}

std::list<Continent*>& Map::get_continents() {
	return *_continents;
}

std::vector<Country*>& Map::get_countries(){
	return *_countries;
}

void Map::unload() {
	
	if (get_continents().size() <= 0 && get_countries().size() <= 0) return;

	std::cout << "\n-- UNLOADING --\n" << std::endl;

	for (Continent* c : get_continents()) delete c;
	for (Country* c : get_countries()) delete c;

	_continents->clear();
	_countries->clear();

	std::cout << "\n-- UNLOADING END --\n" << std::endl;
}

Map::~Map() {
	unload();

	delete _instance;
}
