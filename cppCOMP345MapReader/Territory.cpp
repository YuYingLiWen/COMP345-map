#include "Territory.h"


Territory::Territory(int& index, std::string& territory_name) {
	_index_ptr = &index;
	_name_ptr = &territory_name;
}


std::string Territory::get_name() const{
	return *_name_ptr;
}

int Territory::get_index() const{
	return *_index_ptr;
}

std::string Territory::to_string() {
	return "[" + std::to_string(get_index()) + "] " + get_name();
}

Territory::~Territory() {
	std::cout << "Unloaded:\t" << typeid(Territory).name() << "\t\t" << Territory::get_name() << std::endl;

	delete _index_ptr;
	delete _name_ptr;
}