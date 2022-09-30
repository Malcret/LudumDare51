#pragma once

#include <Core/Core.hpp>
#include <GameState.hpp>
#include <UI.hpp>
#include <Scene.hpp>

#include <MainMenu.hpp>

class Game {
public:
	Game();
	Game(const std::string &name);
	~Game();

	void onUpdate();

	bool isRunning() const;

private:
	std::string m_name;
	sf::RenderWindow *m_pWindow;

	// States
	bool m_isRunning;
	GameState *m_pGameState;

	// Scenes
	MainMenu *m_mainMenu;

	sf::Text *m_pFPSIndicator;
};