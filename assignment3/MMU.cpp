#include "MMU.hpp"
#include<stdexcept>
#include<vector>
#include<iostream>

// to code up: MMU (constructor), storeVal, loadVal, translate

/*
  TIL!!! 
  1. For reference members, initialiser list must be used to 
  initialise the variables when the object is created.
  Otherwise, the user may initialise the variable later in the constructor body
  and we have got a dangling reference waiting to be assigned

  2. When map is declared const, you can't access elements using [] operator
  because that initialises the default value if no value is present.
  Instead, use the ".at()" function
*/
MMU::MMU(Memory& memory, const Config& cfg) : memory(memory), config(cfg){}

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
	for (int i=0, shift = config.addressWidth; i<vaddr_pieces; i++) {
		shift -= config.bitsPerLevel[i];
		try {	// try accessing the map to physical address
			PageTableEntry PTE = memory.getPageTableEntry(i, broken_vaddr[i]);
			paddr |= (PTE.physicalFrame << shift);
		}
		catch(std::runtime_error &e) {
			// std::cout << "For vaddr " << vaddr << ", we are in catch block \n";
			if (!fillInEntries) throw std::runtime_error("No memory allotted");
			// make new page
			PageTableEntry new_page;
			new_page.physicalFrame = memory.nextAvailableFrame;
			new_page.present = true;
			new_page.user = true;
			new_page.write = true;

			memory.nextAvailableFrame += config.pageSize;
			// set the page table entry for this address
			memory.setPageTableEntry(i, broken_vaddr[i], new_page);
			paddr |= (new_page.physicalFrame << shift);
		}
	}
	// add the offset
	uint64_t offset = vaddr & (((uint64_t)1 << config.addressWidth) - 1);
	paddr |= offset; // paddr is fully constructed!
	return paddr;
}
