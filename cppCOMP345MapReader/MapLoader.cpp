#include "MapLoader.h"

#include <iostream>
#include <fstream>


MapLoader* MapLoader::_instance_ptr = nullptr;


MapLoader::MapLoader() {
	// Empty - see instance
}

MapLoader::MapLoader(const MapLoader&  to_copy) {
	_instance_ptr = to_copy.get_instance();
}

void MapLoader::load_map(std::string map_file_name){

	map_file_name = "resources/" + map_file_name + ".map";

	if (!verify(map_file_name)) return; // Map fails basic verifications


	try {
		std::ifstream reader(map_file_name);

		if (reader.is_open()) {

			std::string line;
			FileBlock read_block = FileBlock::None;

			while (std::getline(reader, line)) {

				if (line._Equal(CONTINENTS)) {
					read_block = FileBlock::Continents;
					continue;
				}
				else if (line._Equal(COUNTRIES)) {
					read_block = FileBlock::Countries;
					continue;
				}
				else if (line._Equal(BORDERS)) {
					read_block = FileBlock::Borders;
					continue;
				}
				else if (line[0] == ';' || line.empty()) { // Ignore comments && empty
					continue;
				}

				if (read_block != FileBlock::None) sort_map_file_data(read_block, line);
			}

			reader.close();
		}
		else {
			throw std::runtime_error("Fail to open file @loading map : " + map_file_name);
		}
	}
	catch (std::runtime_error const& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		Map::get_instance()->unload();
		return;
	}
}

void MapLoader::sort_map_file_data(FileBlock &fileBlock, std::string &line)  {

	try {
		switch (fileBlock) {

		case FileBlock::Continents:
			make_continent(split(line));
			break;

		case FileBlock::Borders:
			assign_borders(split(line));
			break;

		case FileBlock::Countries:
			make_countries(split(line));
			break;

		default:
			throw std::runtime_error("Unkown file block. Please reformat file.");
		}
	}
	catch (std::runtime_error const& e) {
		throw e;
	}
}

MapLoader* MapLoader::get_instance() {
	if (_instance_ptr == nullptr) {
		_instance_ptr = new MapLoader();
	}
	return _instance_ptr;
}

std::vector<std::string>& MapLoader::split(std::string& line) const {
	std::vector<std::string>* tokens = new std::vector<std::string>();

	size_t start = 0;
	for (size_t i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			(*tokens).push_back(line.substr(start, i - start));
			start = i + 1;
		}
		else if (i == line.size() - 1) {
			(*tokens).push_back(line.substr(start, i - start + 1));
		}
	}

	return *tokens;
}

void MapLoader::make_continent(std::vector<std::string>& line_tokens) {

	try {

		std::string* continent_name_ptr = new std::string(line_tokens[0]);
		std::string* color_ptr = new std::string(line_tokens[2]);

		if (!is_number(line_tokens[1])) throw std::runtime_error("Army value is not of type int: " + line_tokens[1]);

		int* army_value_ptr = new int(stoi(line_tokens[1]));

		Continent* new_continent = new Continent(*continent_name_ptr, *army_value_ptr, *color_ptr);
		Map::get_instance()->set_continent(*new_continent);
	}
	catch (std::runtime_error e) {
		delete& line_tokens;
		throw e;
	}

	delete& line_tokens;
}

void MapLoader::make_countries(std::vector<std::string>& line_tokens) {

	try {
		std::string* country_name = new std::string(line_tokens[1]);

		if (!is_number(line_tokens[0])) throw std::runtime_error("Country value is not of type int: " + line_tokens[0]);
		if (!is_number(line_tokens[2])) throw std::runtime_error("Continent value is not of type int: " + line_tokens[2]);

		int* country_index_ptr = new int(stoi(line_tokens[0]));
		int* continent_index_ptr = new int(stoi(line_tokens[2]));

		Country* new_country = new Country(*country_index_ptr, *country_name);
		Map::get_instance()->set_country(*continent_index_ptr, *new_country);
	}
	catch (std::runtime_error e) {
		delete& line_tokens;
		throw e;
	}

	delete& line_tokens;
}

void MapLoader::assign_borders(std::vector<std::string>& line_tokens) { 

	try {
		for (std::string& s : line_tokens) if (!is_number(s)) throw new std::runtime_error("Border is not of type int: " + s);

		Map::get_instance()->set_border(line_tokens);
	}
	catch (std::runtime_error const& e) {
		delete& line_tokens;
		throw e;
	}
	delete& line_tokens;
}

bool MapLoader::verify(std::string map_file_name) {

	int file_format_tester = 0;

	std::ifstream reader(map_file_name);

	if (reader.is_open()) {

		std::string line;
		FileBlock read_block = FileBlock::None;

		while (std::getline(reader, line)) {
			if (line._Equal(CONTINENTS)
				|| line._Equal(COUNTRIES)
				|| line._Equal(BORDERS))
				file_format_tester++;
		}

		if (file_format_tester != 3) { // 3 for the 3 file blocks (continents, countries, borders)
			throw std::runtime_error("File format is not respected.");
		}

		reader.close();
		return true;
	}
	else {
		throw std::runtime_error("Fail to open file @file format verifier: " + map_file_name);
	}

	return false;
}

bool MapLoader::is_number(std::string& str) {
	for (char& s : str) if (!isdigit(s)) return false;
	return true;
}

MapLoader& MapLoader::operator=(const MapLoader& loader) {
	_instance_ptr = loader.get_instance();
	return *_instance_ptr;
}


MapLoader::~MapLoader() {
	delete _instance_ptr;
}


std::ostream& operator<<(std::ostream stream, MapLoader& loader) {
	stream << "Map loader stream. Nothing else to display.\n";
	return stream;
}
