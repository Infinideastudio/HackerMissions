#include "Blocks.h"

#define id2name(ID,NAME) case ID : return NAME 

std::string getBlockName(int blockID){
	switch (blockID){
		id2name(0, "ground");
		id2name(1, "wall");
	default:
		return "error";
	}
}