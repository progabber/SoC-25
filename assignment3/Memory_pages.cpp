#include "Memory.hpp"
#include<stdexcept>
#include<iostream>


// to code: Memory(constructor), setPageTableEntry, getPageTableEntry

Memory::Memory(Config& cf) {
	// initialise memory according to configuration in "cf"
	nextAvailableFrame = 0;

	// initialise number of levels in pageTables 
	// (pageTables is a vector, so have to specify size for indexing)
	pageTables.resize(cf.pageTableLevels);
}

void Memory::setPageTableEntry(uint32_t level, uint32_t index, const PageTableEntry& entry) {
	pageTables[level][index].physicalFrame = entry.physicalFrame;
	pageTables[level][index].present = entry.present;
	pageTables[level][index].user = entry.user; 
	pageTables[level][index].write = entry.write; 
}

PageTableEntry Memory::getPageTableEntry(uint32_t level, uint32_t index) const {
	if (pageTables[level].find(index) == pageTables[level].end()) {
		// memory has not been allotted
		throw std::runtime_error("Memory has not been allotted");
	}
	// std::cout << "level" << level << ' '<< "index" << index << '\t';
	/*
	for (auto x : pageTables[level]) {
		std :: cout << "Virt address: " << x.first << "\tReal address: " << x.second.physicalFrame << ' ';
	}
	std::cout << '\n';
	*/
	if (!pageTables[level].at(index).user) {
		throw std::runtime_error("Tried to access kernel page");
	}
	return pageTables[level].at(index);
}
