#include "Block.h"



Block::Block()
{
	T = 100;
	N_t = 0; //default the Block to  be empty of gas
	N_max = 255;

	/*Temporary - replace with number of Gases from GameData*/
	size_t numGases = 2;
	/*Temporary - replace with number of Gases from GameData*/

	N.resize(numGases);
	for (size_t i = 0; i < numGases; i++)
	{
		N[i] = 0; //default the Block to be empty of gas
	}

	name = "default";
	tileID = 0;
}


Block::~Block()
{
}
