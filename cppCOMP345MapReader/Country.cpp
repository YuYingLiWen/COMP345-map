#include "Country.h"

Country::Country(int& index, std::string& country_name) : Territory(index, country_name) {
	_visited_ptr = new bool(false);		
	_neighbor_countries = new std::list<Country*>();
	_army = new int(0);
}

std::list<Country*>& Country::get_neighbors() {
	return *_neighbor_countries;
}

void Country::set_neighbor(Country& bordered_country) {
	_neighbor_countries->push_back(&bordered_country);
}

std::string Country::to_string() {
	std::string tmp = "";

	for (Country* c : get_neighbors()) tmp += "\t>> " + std::to_string(c->get_index()) + " " + c->get_name() + "\n";

	return Territory::to_string() + "\n" + tmp;
}

bool& Country::get_visited() {
	return *_visited_ptr;
}

void Country::set_visited(bool& visited) {

	delete _visited_ptr;
	_visited_ptr = &visited;	
}

int& Country::get_army() {
	return *_army;
}

void Country::set_army(int& army) {
	_army = &army;
}

Country::~Country() {

	std::cout << "Unloaded:\t" << typeid(Country).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _neighbor_countries;
	delete _visited_ptr;
	delete _army;
}
