#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class RenderQue : public sf::Drawable, public sf::Transformable
{
public:
	RenderQue();
	~RenderQue();

	void add(sf::VertexArray &input); //add an array of triangles to the qeue
	void prepare(); //prepare the qeue for rendering
	void reset(); //reset the qeue after rendering

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_texture;
	size_t n; //number of current vertices in the qeue
};