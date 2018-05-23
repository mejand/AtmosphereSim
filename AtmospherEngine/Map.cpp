#include "Map.h"



Map::Map()
{
	width = 10;
	depth = 10;
	height = 10;

	Blocks.resize(width * depth * height, Block());
}


Map::Map(size_t mapSize[3])
{
	width = mapSize[0];
	depth = mapSize[1];
	height = mapSize[2];

	Blocks.resize(width * depth * height, Block());
}


Map::~Map()
{
}


void Map::draw(RenderQue &que, size_t zLevel)
{
	unsigned int GridSize = 20;

	for (size_t y = 0; y < depth; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			sf::VertexArray temp;
			temp.setPrimitiveType(sf::Triangles);
			temp.resize(6);

			//add the top square
			temp[0].position = sf::Vector2f(x * GridSize, y * GridSize);
			temp[1].position = sf::Vector2f(x * GridSize + GridSize, y * GridSize);
			temp[2].position = sf::Vector2f(x * GridSize, y * GridSize + GridSize);

			//add the bottom square
			temp[3].position = sf::Vector2f(x * GridSize + GridSize, y * GridSize + GridSize);
			temp[4].position = sf::Vector2f(x * GridSize, y * GridSize + GridSize);
			temp[5].position = sf::Vector2f(x * GridSize + GridSize, y * GridSize);

			//set color of vertices
			for (size_t i = 0; i < 6; i++)
			{
				temp[i].color = sf::Color(255, 255, 0, Blocks[x + y * width + zLevel * depth * width].N_t);
			}

			//add obstacle to the renderqeue
			que.add(temp);
		}
	}
}


void Map::setGas(size_t x, size_t y, size_t z, size_t type, unsigned int N_new)
{
	size_t index = getIndex(x, y, z);

	//calculate N_t for the other gases (without N_t)
	unsigned int sum = 0;
	for (size_t i = 0; i < Blocks[index].N.size(); i++)
	{
		if (i != type)
		{
			sum += Blocks[index].N[i];
		}
	}

	//check if there is enough space left
	if (N_new + sum <= Blocks[index].N_max)
	{
		//add the gas
		Blocks[index].N[type] = N_new;

		//update N_t
		Blocks[index].N_t = sum + N_new;
	}
	else
	{
		//add only enough to fill the Block
		Blocks[index].N[type] += Blocks[index].N_max - Blocks[index].N_t;

		//update N_t
		Blocks[index].N_t = Blocks[index].N_max;
	}
}


void Map::addGas(size_t x, size_t y, size_t z, size_t type, int N_new)
{
	size_t index = getIndex(x, y, z);

	//calculate N_t for the other gases (without N_t)
	unsigned int sum = 0;
	for (size_t i = 0; i < Blocks[index].N.size(); i++)
	{
		if (i != type)
		{
			sum += Blocks[index].N[i];
		}
	}

	//check if there is enough space left
	if (Blocks[index].N[type] + N_new + sum <= Blocks[index].N_max)
	{
		//add the gas
		Blocks[index].N[type] += N_new;

		//update N_t
		Blocks[index].N_t += N_new;
	}
	else
	{
		//add only enough to fill the Block
		Blocks[index].N[type] += Blocks[index].N_max - Blocks[index].N_t;

		//update N_t
		Blocks[index].N_t = Blocks[index].N_max;
	}
}


void Map::logic()
{
	gasSim();
}


size_t Map::getIndex(size_t x, size_t y, size_t z)
{
	size_t result;

	result = x + y * width + z * depth * width;

	return result;
}


void Map::gasSim()
{
	int dN[6]; //difference in number of gas atoms between current block and neighbour
	int xN[6] = { 1, -1, 0, 0, 0, 0 }; //offset for x dimension
	int yN[6] = { 0, 0, 1, -1, 0, 0 }; //offset for y dimension
	int zN[6] = { 0, 0, 0, 0, 1, -1 }; //offset for z dimension

	//iterate through the map
	for (size_t x = 0; x < width; x++)
	{
		for (size_t y = 0; y < depth; y++)
		{
			for (size_t z = 0; z < height; z++)
			{
				//check if the block is on the edge of the map
				if (x == 0 || y == 0 || z == 0 || x == width - 1 || y == depth - 1 || z == height - 1) //not optimized!
				{
					//handle constant boundary conditions
				}
				else
				{
					//iterate through the different gas types
					for (size_t i = 0; i < Blocks[getIndex(x, y, z)].N.size(); i++)
					{
						//check nearest neighbours
						for (size_t n = 0; n < 6; n++)
						{
							//calculate deltaN
							dN[n] = Blocks[getIndex(x, y, z)].N[i] - Blocks[getIndex(x + xN[n], y + yN[n], z + zN[n])].N[i];

							//only change N if dN negative -> avoid back and forth
							if (dN[n] < 0)
							{
								addGas(x, y, z, i, 10); //addGas() -> currently buggy: eats gas if there is not enough space in the target block
								addGas(x + xN[n], y + yN[n], z + zN[n], i, -10);
							}
						}
					}
				}
			}
		}
	}
}