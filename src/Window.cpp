#include "../include/Window.h"
#include "../include/Game.h"
#include "../include/Renderer.h"

Window::Window(Game & game, Renderer & renderer)
	: _window(sf::VideoMode({ windowWidth, windowHeight }), "Tetris"),
	_game(game), _renderer(renderer) {
	_window.setFramerateLimit(60);
}

void Window::SetIcon(const sf::Image & icon) {
	_window.setIcon(icon);
}

void Window::Run() {
	sf::Clock clock;
	bool gameOverShown = false;

	while ( _window.isOpen() ) {
		while ( const std::optional event = _window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() ) {
				_window.close();
			} else if ( const auto * key = event->getIf<sf::Event::KeyPressed>() ) {
				switch ( key->code ) {
					case sf::Keyboard::Key::Escape: _window.close(); break;
					case sf::Keyboard::Key::Left: _game.MoveLeft(); break;
					case sf::Keyboard::Key::Right: _game.MoveRight(); break;
					case sf::Keyboard::Key::Down: _game.MoveDown(); break;
					case sf::Keyboard::Key::Z: _game.Rotate(); break;
					case sf::Keyboard::Key::X: _game.HardDrop(); break;
					default: break;
				}
			}
		}

		if ( !_window.isOpen() )
			break;

		_game.Update(clock.restart().asMilliseconds());
		if ( _game.IsGameOver() && !gameOverShown ) {
			_window.setTitle("Tetris - Game Over");
			gameOverShown = true;
		}

		_window.clear();
		_renderer.Draw(_window);
		_window.display();
	}
}
