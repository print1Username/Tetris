#include "../include/Setting.h"
#include "../external/json.hpp"

#include <cassert>
#include <chrono>
#include <filesystem>
#include <fstream>

int main() {
	Setting projectSettings;
	assert(projectSettings.GetWindowWidth() == 800 && projectSettings.GetWindowHeight() == 600);
	assert(projectSettings.GetWindowMode() == "windowed");
	assert(projectSettings.GetCloseKey() == sf::Keyboard::Key::Escape);
	assert(projectSettings.GetLeftKey() == sf::Keyboard::Key::Left);
	assert(projectSettings.GetRightKey() == sf::Keyboard::Key::Right);
	assert(projectSettings.GetDownKey() == sf::Keyboard::Key::Down);
	assert(projectSettings.GetRotateKey() == sf::Keyboard::Key::Z);
	assert(projectSettings.GetHardDropKey() == sf::Keyboard::Key::X);

	const auto folder = std::filesystem::temp_directory_path() /
		("tetris_setting_smoke_" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
	std::filesystem::create_directories(folder);
	const auto path = folder / "settings.json";

	std::ofstream(path).close();
	Setting empty(path.string());
	assert(empty.GetWindowWidth() == 800 && empty.GetWindowHeight() == 600);
	assert(empty.GetWindowMode() == "windowed");
	assert(empty.GetCloseKey() == sf::Keyboard::Key::Escape);
	assert(empty.GetLeftKey() == sf::Keyboard::Key::Left);
	assert(empty.GetRightKey() == sf::Keyboard::Key::Right);
	assert(empty.GetDownKey() == sf::Keyboard::Key::Down);
	assert(empty.GetRotateKey() == sf::Keyboard::Key::Z);
	assert(empty.GetHardDropKey() == sf::Keyboard::Key::X);
	{
		std::ifstream file(path);
		const auto data = nlohmann::json::parse(file);
		assert(data.at("window").at("width") == 800);
		assert(data.at("keyboard").contains("hardDrop"));
	}

	const nlohmann::json configuredData = {
		{ "window", { { "width", 1024 }, { "height", 768 }, { "mode", "windowed" } } },
		{ "keyboard", {
			{ "close", static_cast<int>(sf::Keyboard::Key::Escape) },
			{ "left", static_cast<int>(sf::Keyboard::Key::A) },
			{ "right", static_cast<int>(sf::Keyboard::Key::Right) },
			{ "down", static_cast<int>(sf::Keyboard::Key::Down) },
			{ "rotate", static_cast<int>(sf::Keyboard::Key::Z) },
			{ "hardDrop", static_cast<int>(sf::Keyboard::Key::X) }
		} }
	};
	std::ofstream(path) << configuredData.dump();
	Setting configured(path.string());
	assert(configured.GetWindowWidth() == 1024 && configured.GetWindowHeight() == 768);
	assert(configured.GetLeftKey() == sf::Keyboard::Key::A);
	assert(configured.GetRightKey() == sf::Keyboard::Key::Right);

	std::ofstream(path) << R"({"window":{"width":1024}})";
	Setting partial(path.string());
	assert(partial.GetWindowWidth() == 1024 && partial.GetWindowHeight() == 600);
	{
		std::ifstream file(path);
		const auto data = nlohmann::json::parse(file);
		assert(data.at("window").at("height") == 600);
		assert(data.at("keyboard").contains("left"));
	}

	std::ofstream(path) << R"({"window":{"width":0,"height":600,"mode":"windowed"},"keyboard":{"close":999}})";
	Setting invalidFields(path.string());
	assert(invalidFields.GetWindowWidth() == 800);
	assert(invalidFields.GetCloseKey() == sf::Keyboard::Key::Escape);
	{
		std::ifstream file(path);
		const auto data = nlohmann::json::parse(file);
		assert(data.at("window").at("width") == 800);
		assert(data.at("keyboard").at("close") == static_cast<int>(sf::Keyboard::Key::Escape));
	}

	std::ofstream(path) << "invalid json";
	Setting invalid(path.string());
	assert(invalid.GetWindowWidth() == 800);
	{
		std::ifstream file(path);
		assert(nlohmann::json::parse(file).at("window").at("width") == 800);
	}

	std::filesystem::remove(path);
	Setting missing(path.string());
	assert(missing.GetWindowWidth() == 800);
	assert(std::filesystem::exists(path));
	std::filesystem::remove_all(folder);
}
