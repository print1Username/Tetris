#include "../include/Setting.h"
#include "../external/json.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <limits>

namespace {
	using json = nlohmann::json;

	bool ReadSize(const json & object, const char * name, unsigned & result) {
		if ( !object.contains(name) || !object.at(name).is_number_unsigned() )
			return false;

		const auto value = object.at(name).get<std::uint64_t>();
		if ( value == 0 || value > std::numeric_limits<unsigned>::max() )
			return false;

		result = static_cast<unsigned>(value);
		return true;
	}

	bool ReadKey(const json & object, const char * name, sf::Keyboard::Key & result) {
		if ( !object.contains(name) || !object.at(name).is_number_unsigned() )
			return false;

		const auto value = object.at(name).get<std::uint64_t>();
		if ( value >= sf::Keyboard::KeyCount )
			return false;

		result = static_cast<sf::Keyboard::Key>(value);
		return true;
	}
}

Setting::Setting(const std::string & path) : _path(path) {
	Load();
}

void Setting::Load() {
	std::ifstream file(_path);
	json data = json::parse(file, nullptr, false);
	bool complete = data.is_object();

	if ( complete ) {
		if ( !data.contains("window") || !data.at("window").is_object() ) {
			complete = false;
		} else {
			const auto & window = data.at("window");
			complete = ReadSize(window, "width", _windowWidth) && complete;
			complete = ReadSize(window, "height", _windowHeight) && complete;
			if ( window.value("mode", json()) == "windowed" )
				_windowMode = "windowed";
			else
				complete = false;
		}

		if ( !data.contains("keyboard") || !data.at("keyboard").is_object() ) {
			complete = false;
		} else {
			const auto & keyboard = data.at("keyboard");
			complete = ReadKey(keyboard, "close", _closeKey) && complete;
			complete = ReadKey(keyboard, "left", _leftKey) && complete;
			complete = ReadKey(keyboard, "right", _rightKey) && complete;
			complete = ReadKey(keyboard, "down", _downKey) && complete;
			complete = ReadKey(keyboard, "rotate", _rotateKey) && complete;
			complete = ReadKey(keyboard, "hardDrop", _hardDropKey) && complete;
		}
	}

	if ( !complete )
		Save();
}

bool Setting::Save() const {
	const json data = {
		{ "window", {
			{ "width", _windowWidth },
			{ "height", _windowHeight },
			{ "mode", _windowMode }
		} },
		{ "keyboard", {
			{ "close", static_cast<int>(_closeKey) },
			{ "left", static_cast<int>(_leftKey) },
			{ "right", static_cast<int>(_rightKey) },
			{ "down", static_cast<int>(_downKey) },
			{ "rotate", static_cast<int>(_rotateKey) },
			{ "hardDrop", static_cast<int>(_hardDropKey) }
		} }
	};

	const std::filesystem::path path(_path);
	if ( path.has_parent_path() ) {
		std::error_code error;
		std::filesystem::create_directories(path.parent_path(), error);
		if ( error )
			return false;
	}

	std::ofstream file(_path);
	if ( !file )
		return false;

	file << data.dump(2) << '\n';
	return static_cast<bool>(file);
}
