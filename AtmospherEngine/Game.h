#pragma once
#include <SFML\Graphics.hpp>


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
};

