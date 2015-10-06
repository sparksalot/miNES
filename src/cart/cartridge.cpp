#include "cartridge.h"
#include "loaders/ines/ines.h"

#include <iostream>
#include <fstream>
#include <cstring>

#define INES_EXT ".nes"

using namespace cart;

class Mapper1Cart : public Cartridge {

};


namespace {

enum RomFormat
{
	Unknown,
	INes,
	Unif,
	Fds
};

// uses the extension of the file to match against known rom types.
RomFormat getRomFileType(std::string &path) {
	RomFormat t = Unknown;
	if (path.length() > strlen(INES_EXT) && 
		path.compare(path.length()-strlen(INES_EXT), strlen(INES_EXT), INES_EXT) == 0) {
		t = INes;
	}

	return t;
}

}

std::unique_ptr<Cartridge> cart::loadCart(std::string &path) {
	std::unique_ptr<Cartridge> res;
	std::ifstream file;

	file.open(path, std::ios::binary|std::ios::in);

	if (file.is_open()) {
		switch(getRomFileType(path)) {
			case INes:
			res = loaders::ines::load(file);
			break;

			// handle default and unknown cases.
			default:
			break;
		}
	}

	return res;
}