#pragma once
#include <SFML\Graphics.hpp>
#include "Map.h"


enum GameState { END, PLAYING, PAUSED };

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void setup();
	void input();
	void logic();
	void draw();

	sf::RenderWindow window;
	GameState gamestate;

	Map map; //Game Map
	RenderQue renderque;
	size_t activeZLevel;
};

