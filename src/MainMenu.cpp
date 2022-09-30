#include <PCH.hpp>
#include <MainMenu.hpp>

MainMenu::MainMenu()
	: Scene() {}

MainMenu::MainMenu(GameState *pGameState)
	: Scene(pGameState) {}

MainMenu::~MainMenu() {}

void MainMenu::onEvent(sf::Event &event) {
	sf::Vector2i pos = sf::Mouse::getPosition(*m_pGameState->getWindow());
	LOG_TRACE("Mouse Position: {0}x{1}", pos.x, pos.y);
}

void MainMenu::onUpdate() {

}