#include <Game.hpp>

int main() {
	Game *pGame = new Game("Ludum Dare 51");

	LOG_TRACE("Run game...");
	while (pGame->isRunning()) {
		pGame->onUpdate();
	}

	delete pGame;

	return 0;
}
