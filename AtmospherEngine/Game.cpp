#include "Game.h"



Game::Game()
{
	setup();
}


Game::~Game()
{
}


void Game::run()
{
	//game loop
	while (gamestate != END)
	{
		input();
		logic();
		draw();
	}
}


void Game::setup()
{
	//setup the window
	window.create(sf::VideoMode(800, 600), "Atmosphere");
	window.setVerticalSyncEnabled(true);

	//setup Game State
	gamestate = PLAYING;

	activeZLevel = 1;

	/*Debug - add some gas to the Map*/
	map.setGas(1, 1, 1, 0, 200);
	map.setGas(2, 2, 1, 0, 200);
	map.setGas(3, 3, 1, 0, 100);
	map.setGas(3, 0, 0, 0, 200);
	map.setGas(0, 4, 0, 0, 200);
}


void Game::input()
{
	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			window.close();
			gamestate = END;
		}
	}
}


void Game::logic()
{

}


void Game::draw()
{
	window.clear();

	map.draw(renderque, activeZLevel);

	renderque.prepare();
	window.draw(renderque);
	renderque.reset();

	window.display();
}