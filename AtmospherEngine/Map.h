#pragma once
#include "Block.h"
#include "RenderQue.h"

class Map
{
public:
	Map();
	Map(size_t mapSize[3], size_t numGases, unsigned int gasBorder);
	~Map();

	void draw(RenderQue &que, size_t zLevel); //add the map to the renderque
	void setGas(size_t x, size_t y, size_t z, size_t type, unsigned int N_new);
	void logic(); //advance one timestep

private:
	size_t width, depth, height; //x,y,z dimensions of the Map
	std::vector<Block> Blocks; //3D grid containing all blocks on the map
	std::vector<unsigned int> N_border; //boundary conditions of the map

	size_t getIndex(size_t x, size_t y, size_t z); //return the index based on the x, y, z coordinates
	void gasSim(); //gas simulation
	int addGas(size_t x, size_t y, size_t z, size_t type, int N_new);
};

