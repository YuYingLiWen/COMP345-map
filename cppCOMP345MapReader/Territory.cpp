#include "Territory.h"


Territory::Territory(const Territory&  to_copy) {
	_index_ptr = new int(to_copy.get_index());
	_name_ptr = new std::string(to_copy.get_name());
}

Territory::Territory(int& index, std::string& territory_name) {
	_index_ptr = &index;
	_name_ptr = &territory_name;
}

void Territory::set_index(int& new_index) {
	_index_ptr = &new_index;
}

void Territory::set_name(std::string& new_name) {
	_name_ptr = &new_name;
}


std::string& Territory::get_name() const{
	return *_name_ptr;
}

int& Territory::get_index() const{
	return *_index_ptr;
}

std::string Territory::to_string() const{
	return "[" + std::to_string(get_index()) + "] " + get_name();
}

Territory& Territory::operator=(const Territory& territory) {
	delete _index_ptr;
	delete _name_ptr;

	set_index(*new int(territory.get_index()));
	set_name(*new std::string(territory.get_name()));

	return *this;
}

Territory::~Territory() {
	std::cout << "Unloaded:\t" << typeid(Territory).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _index_ptr;
	delete _name_ptr;
}


std::ostream& operator << (std::ostream& stream, Territory& territory) {
	stream << territory.to_string();
	return stream;
}
