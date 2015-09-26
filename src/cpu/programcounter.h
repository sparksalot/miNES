#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

// Library
#include <stdint.h>

namespace cpu {
	union ProgramCounter {
			uint16_t pc;
			struct {
					uint8_t pcl;
					uint8_t pch;
			} r;
	};
}
#endif
