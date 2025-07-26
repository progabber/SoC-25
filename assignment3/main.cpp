#include<iostream>
#include<vector>
#include "MMU.hpp"

int main(){
	struct Config config = {
		32,
		4096,
		2,
		{10, 10},
		1234123412
	};

	Memory memory(config);
	MMU mmu(memory, config);

	mmu.storeVal(0, 12);
	mmu.storeVal(4, 44);
	std::cout << mmu.loadVal(0) << ' ' << mmu.loadVal(4) << std::endl;
	mmu.storeVal(4, 10);
	std::cout << mmu.loadVal(4) << std::endl;
}
