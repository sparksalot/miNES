#ifndef MEM_H
#define MEM_H

#define MEM_SIZE 0xffff

namespace mem {
	typedef Word uint8_t;
	class Mem
	{
	public:
		Mem();
		void store(Word w, uint8_t addr);
		Word load(uint8_t addr);
		void reset();
		~Mem();
	private:
		Word store[MAX_MEM];
	};

}

#endif