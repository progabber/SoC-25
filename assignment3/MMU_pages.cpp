#include "MMU.hpp"
#include<stdexcept>
#include<vector>
#include<iostream>

// to code up: MMU (constructor), storeVal, loadVal, translate

/*
  TIL!!! 
  For reference members, initialiser list must be used to 
  initialise the variables when the object is created.
  Otherwise, the user may initialise the variable later in the constructor body
  and we have got a dangling reference waiting to be assigned
*/
MMU::MMU(Memory& memory, const Config& cfg) : memory(memory), config(cfg){
    cr3 = memory.nextAvailableFrame;
    memory.nextAvailableFrame += cfg.pageSize;
}

void MMU::storeVal(uint64_t vaddr, uint64_t val) {
	// store value "val" in the virtual address "vaddr"

	// get the physical address from translate by allotting physical frames 
	// if no mappings are present
	uint64_t paddr = translate(vaddr, true); // physical address
	memory.memory_contents[paddr] = val; // assign the value to paddr
}

uint64_t MMU::loadVal(uint64_t vaddr) {
	// load and return value from the virtual address "vaddr"

	// get the physical address from translate and 
	// throw an error if pages are missing in bw
	try{
		uint64_t paddr = translate(vaddr, false);
		return memory.memory_contents[paddr];
	}
	catch(std::runtime_error &e) {
		throw std::runtime_error("No mappings found");
	}
}

uint64_t MMU::translate(uint64_t vaddr, bool fillInEntries) { // fillInEntries: fill page table
	// translate the virtual address to a physical address
	uint64_t paddr = 0; // physical address

	// chop up vaddr into pieces except the offset
	int vaddr_pieces = config.pageTableLevels;
	std::vector<uint32_t> broken_vaddr(vaddr_pieces); 
	int l = config.addressWidth;
	int r = config.addressWidth;
	for (int i=0; i < vaddr_pieces; i++) {
		r -= config.bitsPerLevel[i];
		uint32_t mask = (((uint32_t)1 << l) - ((uint32_t)1 << r));
		broken_vaddr[i] = (mask & vaddr);
		l = r; 
	}

	// calculate physical frame for each piece (level) of vaddr
	// and modify "paddr" accordingly
    uint64_t current_physical_frame = cr3;
	for (int i=0, shift = config.addressWidth; i<vaddr_pieces; i++) {
        uint32_t offset_in_current_physical_frame = broken_vaddr[i];
        uint32_t pte_location = current_physical_frame | offset_in_current_physical_frame;
        if (memory.memory_contents.find(pte_location) 
                == memory.memory_contents.end()) {
            if (!fillInEntries) 
                throw std::runtime_error("No memory allotted");
            // otherwise make the mappings
            memory.memory_contents[pte_location] = memory.nextAvailableFrame;
            memory.nextAvailableFrame += config.pageSize;
        }
        current_physical_frame = memory.memory_contents.at(pte_location);
	}
	// add the offset
	uint32_t offset = vaddr & (config.pageSize - 1);
	current_physical_frame |= offset; // paddr is fully constructed!
	return current_physical_frame;
}
