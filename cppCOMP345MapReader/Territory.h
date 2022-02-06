#pragma once

#include <string>
#include <iostream> // To be removed
#include <vector>
#include <list>

class Territory
{

	int* _index_ptr;
	std::string* _name_ptr;

private:
	void set_index(int& new_index);
	void set_name(std::string& new_name);

public:
	Territory() = delete; // Prevent accidental use

	//Copy constructor - !!!Don't use unless really necessary - cause dupe index
	Territory(const Territory& to_copy);

	Territory(int& index, std::string& territory_name);
	~Territory();

	std::string to_string() const; // Display obj as string



	std::string& get_name() const;
	int& get_index() const;

	Territory& operator=(const Territory& territory);

	friend std::ostream& operator << (std::ostream & stream, Territory & territory); 

	friend class Country;
	friend class Continent;
};


//********** Global scope utility functions ********//

template <typename T>
std::list<T*>& copy(std::list<T*> to_copy) {
	std::list<T*>* tmp = new std::list<T*>();

	for (T* t : to_copy) (*tmp).push_back(t);

	return *tmp;
}

template <typename T>
std::vector<T*>& copy(std::vector<T*> to_copy) {
	std::vector<T*>* tmp = new std::vector<T*>();

	for (T* t : to_copy) (*tmp).push_back(t);

	return *tmp;
}