#ifndef MEM_H
#define MEM_H

#include <stdint.h>

#define MEM_SIZE 0xFFFF

namespace mem {
	typedef uint8_t Word;
	class Mem
	{
		public:
			Mem();
			~Mem();

			void store(Word w, uint8_t addr);
			Word load(uint8_t addr);
			void reset();
		private:
			uint8_t bank[MEM_SIZE];
	};
}

#endif