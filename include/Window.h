#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Renderer;

class Window {
public:
	static constexpr unsigned windowWidth = 800;
	static constexpr unsigned windowHeight = 600;

	Window(Game & game, Renderer & renderer);
	void SetIcon(const sf::Image & icon);
	void Run();

private:
	sf::RenderWindow _window;
	Game & _game;
	Renderer & _renderer;
};
