#ifndef _H_CART_LOADERS_INES
#define _H_CART_LOADERS_INES

#include <memory>
#include <iostream>
#include <fstream>

namespace cart {
	class Cartridge;
namespace loaders {
namespace ines {

std::unique_ptr<Cartridge> load(std::ifstream &file);


}
}
}

#endif