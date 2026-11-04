#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>

class Setting {
public:
	explicit Setting(const std::string & path = "assets/config/settings.json");

	unsigned GetWindowWidth() const { return _windowWidth; }
	unsigned GetWindowHeight() const { return _windowHeight; }
	const std::string & GetWindowMode() const { return _windowMode; }
	sf::Keyboard::Key GetCloseKey() const { return _closeKey; }
	sf::Keyboard::Key GetLeftKey() const { return _leftKey; }
	sf::Keyboard::Key GetRightKey() const { return _rightKey; }
	sf::Keyboard::Key GetDownKey() const { return _downKey; }
	sf::Keyboard::Key GetRotateKey() const { return _rotateKey; }
	sf::Keyboard::Key GetHardDropKey() const { return _hardDropKey; }

	bool Save() const;

private:
	std::string _path;
	unsigned _windowWidth = 800;
	unsigned _windowHeight = 600;
	std::string _windowMode = "windowed";
	sf::Keyboard::Key _closeKey = sf::Keyboard::Key::Escape;
	sf::Keyboard::Key _leftKey = sf::Keyboard::Key::Left;
	sf::Keyboard::Key _rightKey = sf::Keyboard::Key::Right;
	sf::Keyboard::Key _downKey = sf::Keyboard::Key::Down;
	sf::Keyboard::Key _rotateKey = sf::Keyboard::Key::Z;
	sf::Keyboard::Key _hardDropKey = sf::Keyboard::Key::X;

	void Load();
};
