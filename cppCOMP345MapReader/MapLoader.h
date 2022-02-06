#pragma once

#include <string>
#include <list>
#include <vector>

#include "Continent.h"
#include "Map.h"

#define CONTINENTS "[continents]"
#define COUNTRIES "[countries]"
#define BORDERS "[borders]"

class MapLoader
{
	enum class FileBlock { None, Files, Continents, Borders, Countries };

	static MapLoader *_instance_ptr;

public:

	//Copy constructor. !!!Don't use unless really necessary
	MapLoader(const MapLoader&  to_copy);

	~MapLoader();

	void load_map(std::string map_file_name);
	static MapLoader* get_instance();

private:
	MapLoader();

	//Splits read line into a vector.
	std::vector<std::string>& split(std::string& line) const;

	//Checks if a .map file is valid. return: valid=true; invalid=false;
	bool verify(std::string map_file_name);

	//Helper to sort out which obj needs to be created.
	void sort_map_file_data(FileBlock &fileBlock, std::string &line);

	void make_continent(std::vector<std::string>& splited_line);
	void make_countries(std::vector<std::string>& splited_line);
	void assign_borders(std::vector<std::string>& splited_line);

	//Check is string is a number
	bool is_number(std::string& str);

	MapLoader& operator=(const MapLoader& country);

	friend std::ostream& operator<<(std::ostream stream, MapLoader& loader);
};

