#pragma once
#include <string>
#include <vector>


struct Block
{
	Block();
	~Block();

	unsigned int T; //temperature
	unsigned int N_t; //total number of gas atoms currently in the Block
	unsigned int N_max; //maximum number of gas atoms that can be in the block
	std::vector<unsigned int> N; //number of gas atoms per gas type
	std::string name; //name of the block
	unsigned int tileID; //ID of the tile for rendering
};

