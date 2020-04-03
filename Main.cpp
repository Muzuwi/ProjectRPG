#include <SFML/Graphics.hpp>
#include "Engine.hpp"

int main() {
	Engine engine;
	try {
		engine.Start();
	} catch (std::exception& ex) {
		std::cerr << "ProjectRPG has encountered an error and needs to close\n";
		std::cerr << "Details: " << ex.what() << "\n";
	}

	return 0;
}