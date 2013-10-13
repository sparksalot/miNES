#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <stdint.h>

namespace cpu {
	typedef union {
		uint16_t pc;
		struct {
			uint8_t pcl;
			uint8_t pch;
		} r;
	} ProgramCounter;

}
#endif
