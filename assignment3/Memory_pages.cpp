#include "Memory.hpp"

Memory::Memory(Config& cf) {
	// initialise memory according to configuration in "cf"
	nextAvailableFrame = 0;
}

