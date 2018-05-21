#pragma once
#include "Block.h"
#include "RenderQue.h"

class Map
{
public:
	Map();
	Map(size_t mapSize[3]);
	~Map();

	void draw(RenderQue &que, size_t zLevel);
	void setGas(size_t x, size_t y, size_t z, size_t type, unsigned int N_new);

private:
	size_t width, depth, height; //x,y,z dimensions of the Map
	std::vector<Block> Blocks; //3D grid containing all blocks on the map
};

