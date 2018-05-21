#include "RenderQue.h"



RenderQue::RenderQue()
{
	n = 0;

	m_vertices.setPrimitiveType(sf::Triangles);
}


RenderQue::~RenderQue()
{
}


void RenderQue::add(sf::VertexArray &input)
{
	//check if the input contains triangles
	if (input.getPrimitiveType() != sf::Triangles)
	{
		return;
	}

	//calculate the difference between the space left and the size of the input
	int diff = (int(m_vertices.getVertexCount()) - int(n)) - int(input.getVertexCount());

	//if difference is negative: resize the qeue
	if (diff < 0)
	{
		m_vertices.resize(n - diff);
	}

	//add the input to the qeue
	for (size_t i = 0; i < input.getVertexCount(); i++)
	{
		m_vertices[n + i] = input[i];
	}

	//add to n
	n += input.getVertexCount();
}


void RenderQue::prepare()
{
	//check if the renderqeue has empty spots left
	if (n < m_vertices.getVertexCount())
	{
		m_vertices.resize(n);
	}
}


void RenderQue::reset()
{
	n = 0;
	m_vertices.clear();
}


void RenderQue::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

										// apply the texture
	states.texture = &m_texture;

	// draw the vertex array
	target.draw(m_vertices, states);
}