#include "RenderQue.h"



RenderQue::RenderQue()
{
	for (size_t i = 0; i < 7; i++)
	{
		n[i] = 0;
	}

	vertexBuffer[0].setPrimitiveType(sf::Points);
	vertexBuffer[1].setPrimitiveType(sf::Lines);
	vertexBuffer[2].setPrimitiveType(sf::LineStrip);
	vertexBuffer[3].setPrimitiveType(sf::Triangles);
	vertexBuffer[4].setPrimitiveType(sf::TriangleStrip);
	vertexBuffer[5].setPrimitiveType(sf::TriangleFan);
	vertexBuffer[6].setPrimitiveType(sf::Quads);
}


RenderQue::~RenderQue()
{
}


void RenderQue::add(sf::VertexArray &input)
{
	//check what type of vertex array is being added
	size_t type = 0;
	if (input.getPrimitiveType() == sf::Triangles)
	{
		type = 3;
	}
	else if (input.getPrimitiveType() == sf::LineStrip)
	{
		type = 2;
	}
	else if (input.getPrimitiveType() == sf::Lines)
	{
		type = 1;
	}
	else if (input.getPrimitiveType() == sf::TriangleStrip)
	{
		type = 4;
	}
	else if (input.getPrimitiveType() == sf::TriangleFan)
	{
		type = 5;
	}
	else if (input.getPrimitiveType() == sf::Quads)
	{
		type = 6;
	}

	//calculate the difference between the space left and the size of the input
	int diff = (int(vertexBuffer[type].getVertexCount()) - int(n[type])) - int(input.getVertexCount());

	//if difference is negative: resize the qeue
	if (diff < 0)
	{
		vertexBuffer[type].resize(n[type] - diff);
	}

	//add the input to the qeue
	for (size_t i = 0; i < input.getVertexCount(); i++)
	{
		vertexBuffer[type][n[type] + i] = input[i];
	}

	//add to n
	n[type] += input.getVertexCount();
}


void RenderQue::prepare()
{
	//check if the renderqeue has empty spots left
	for (size_t i = 0; i < 7; i++)
	{
		if (n[i] < vertexBuffer[i].getVertexCount())
		{
			vertexBuffer[i].resize(n[i]);
		}
	}
}


void RenderQue::reset()
{
	for (size_t i = 0; i < 7; i++)
	{
		n[i] = 0;
		vertexBuffer[i].clear();
	}
}


void RenderQue::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

										// apply the texture
	states.texture = &m_texture;

	// draw the vertex array
	for (size_t i = 0; i < 7; i++)
	{
		target.draw(vertexBuffer[i], states);
	}
}