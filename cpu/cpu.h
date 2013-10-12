#include "instuction"
#include <stdint.h>

namespace cpu {
	class Cpu
	{
	public:
		Cpu(arguments);
		void tick(void);
		void fetch(void);
		void loadInstuction(Instuction i);
		~Cpu();
	private:
		uint16_t pc;
	};

}