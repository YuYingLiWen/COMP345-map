#include <iostream>
#include <thread>
#include <string>

#include "MapLoader.h"

#define BERLIN "berlin"
#define CANADA "canada"
#define COW "cow"
#define ESTONIA "estonia"
#define FORTERESS "fortress"
#define INVALID1 "invalid1"
#define INVALID2 "invalid2"


int main() {

	bool run = true;

	while (run) {

		try {
			int map;
			do {
				std::cout << "Please choose from 0 to 7." << std::endl;
				
				std::cin >> map;

				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					map = -1;
				}
			} while (map > 7 || map < 0);

			switch (map)
			{
			case 1:
				MapLoader::get_instance()->load_map(BERLIN);
				break;

			case 2:
				MapLoader::get_instance()->load_map(CANADA);
				break;

			case 3:
				MapLoader::get_instance()->load_map(COW);
				break;

			case 4:
				MapLoader::get_instance()->load_map(ESTONIA);
				break;

			case 5:
				MapLoader::get_instance()->load_map(FORTERESS);
				break;

			case 6:
				MapLoader::get_instance()->load_map(INVALID1);
				break;

			case 7:
				MapLoader::get_instance()->load_map(INVALID2);
				break;

			case 0:
				run = false;
				break;

			default:
				std::cout << "asdfqweroqiwueorpqwer." << std::endl;

				break;
			}
		}
		catch (std::runtime_error e) {
			std::cout << "ERROR: " << e.what() << std::endl;
			Map::get_instance()->unload();
		}

		if (run) {
			Map::get_instance()->display();
			Map::get_instance()->validate();
			Map::get_instance()->unload();
		}
	}

	return 0;
}