#ifndef _H_CART_CARTRIDGE
#define _H_CART_CARTRIDGE

#include <cstdint>
#include <memory>
#include <string>

namespace cart {
	class Cartridge {
		public:
			virtual void store(uint8_t w, uint16_t addr);
			virtual uint8_t load(uint16_t addr);
			virtual ~Cartridge();
	};

	std::unique_ptr<Cartridge> loadCart(std::string &path);
}

#endif