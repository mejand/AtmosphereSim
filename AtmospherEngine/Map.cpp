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
	size_t index = x + y * width + z * depth * width;

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