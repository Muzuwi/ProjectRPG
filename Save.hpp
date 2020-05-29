#pragma once
#include <fstream>
#include "JsonOverloads.hpp"
#include "Tools/json.hpp"

class Savefile {
	nlohmann::json& contents;
public:
	Savefile(nlohmann::json& v)
	: contents(v){}

	template<class T>
	T get(const std::string& key) const {
		try {
			return contents[key].get<T>();
		} catch (const std::exception&) {
			return T{};
		}
	}

	template<class T>
	void set(const std::string& key, const T& value) {
		contents[key] = value;
	}

	bool exists(const std::string& key) {
		return contents.find(key) != contents.end();
	}

	void saveToFile() {
		std::ofstream file{"GameContent/Savegame.json"};
		if(!file.good()) {
			std::cerr << "Failed saving savefile to file\n";
			return;
		}
		file << contents.dump(1, '\t');
		file.close();
	}
};