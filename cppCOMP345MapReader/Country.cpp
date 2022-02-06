#include "Country.h"


Country::Country(const Country& to_copy) : Territory(*new int(to_copy.get_index()), *new std::string(to_copy.get_name())) {

	_player_ptr = to_copy.check_claim();
	_visited_ptr = new bool(to_copy.get_visited());
	_neighbor_countries_ptr = &copy(to_copy.get_neighbors());
	_stationed_army_ptr = new int(to_copy.get_stationed_army());

}

Country::Country(int& index, std::string& country_name) : Territory(index, country_name) {

	_player_ptr = nullptr;
	_visited_ptr = new bool(false);		
	_neighbor_countries_ptr = new std::list<Country*>();
	_stationed_army_ptr = new int(0);
}

std::list<Country*>& Country::get_neighbors() const {
	return *_neighbor_countries_ptr;
}

void Country::set_neighbor(Country& bordered_country) {
	_neighbor_countries_ptr->push_back(&bordered_country);
}

std::string Country::to_string() {
	std::string tmp = "";

	for (Country* c : get_neighbors()) tmp += "\t>> " + std::to_string(c->get_index()) + " " + c->get_name() + "\n";

	return Territory::to_string() + "\n" + tmp;
}

bool& Country::get_visited() const {
	return *_visited_ptr;
}

void Country::set_visited(bool& visited) {

	delete _visited_ptr;
	_visited_ptr = &visited;	
}

int& Country::get_stationed_army() const {
	return *_stationed_army_ptr;
}

void Country::set_stationed_army(int& army) {
	_stationed_army_ptr = &army;
}

Country& Country::operator=(const Country& country) {
	
	delete& get_name();
	delete& get_index();
	delete _neighbor_countries_ptr;
	delete _visited_ptr;
	delete _stationed_army_ptr;

	set_name(*new std::string(country.get_name()));
	set_index(*new int(country.get_index()));
	_visited_ptr = new bool(country.get_visited());
	_neighbor_countries_ptr = &copy(country.get_neighbors());
	_stationed_army_ptr = new int(country.get_stationed_army());

	return *this;
}

void Country::claim(Player& player) {
	_player_ptr = &player;
}

Player* Country::check_claim() const{
	return _player_ptr;
}

Country::~Country() {

	std::cout << "Unloaded:\t" << typeid(Country).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _neighbor_countries_ptr;
	delete _visited_ptr;
	delete _stationed_army_ptr;
}

std::ostream& operator<<(std::ostream& stream, Country& country) {
	stream << country.to_string();
	return stream;
}
