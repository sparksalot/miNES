#include "cartridge.h"

#include <iostream>
#include <fstream>
#include <cstring>

#define INES_EXT ".nes"

using namespace cart;

class Mapper1Cart : public Cartridge {

};

std::unique_ptr<Cartridge> loadINesCart(std::ifstream &file) {
	std::unique_ptr<Cartridge> res;

 return res;
}

enum RomFormat
{
	Unknown,
	INes,
	Unif,
	Fds
};

RomFormat getRomFileType(std::string &path) {
	RomFormat t = Unknown;
	if (path.length() > strlen(INES_EXT) && 
		path.compare(path.length()-strlen(INES_EXT), strlen(INES_EXT), INES_EXT)) {
		t = INes;
	}

	return t;
}

std::unique_ptr<Cartridge> cart::loadCart(std::string &path) {
	std::unique_ptr<Cartridge> res;
	std::ifstream file;

	file.open(path);

	if (file.is_open()) {
		switch(getRomFileType(path)) {
			case INes:
			res = loadINesCart(file);
			break;

			// handle default and unknown cases.
			case Unknown:
			default:
			break;
		}
	}

	return res;
}