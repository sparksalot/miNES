#include "ines.h"

#include "../../cartridge.h"

using namespace cart::loaders::ines;

#define INES_HEADER_SIZE 16

namespace {
struct inesHeader {
	union {
		struct {
			uint8_t magic[4]; // Should be NES<EOF>
			uint8_t numProgPages; // prog page is 16384 bytes.
			uint8_t numCharPAges; // char page is 8192 bytes.
			uint8_t Flags6;
			uint8_t Flags7;
			uint8_t unused[8];
		};
		uint8_t data [INES_HEADER_SIZE];
	};
};

bool isValidInesHeader(inesHeader header) {
	auto res = true;
	if (header.magic[0] == 'N' && 
			header.magic[1] == 'E' && 
			header.magic[2] == 'S') { // Todo(jake) should be NES<EOF>
		for (auto i = 11; i < 16; i++) {
			if (header.data[i] != 0) {
				res = false;
			}
		}
	} else {
		res = false;
	}

	return res;
}

}

std::unique_ptr<cart::Cartridge> cart::loaders::ines::load(std::ifstream &file) {
	std::unique_ptr<cart::Cartridge> res;
	inesHeader head;
	file.read(reinterpret_cast<char*>(&head), sizeof(head));
	if (file) {
		// validate the header 
		if (isValidInesHeader(head)) { // Todo(jake) should be NES<EOF>

		} else {
			std::cerr << "Did not detect valid ines header." << std::endl;
		}
	} else {
		std::cerr << "Failed to read header." << std::endl;
	}
	return res;
}