#pragma once

#include <Scene.hpp>

class MainMenu : public Scene {
public:
	MainMenu();
	MainMenu(GameState *pGameState);
	virtual ~MainMenu();

	virtual void onEvent(sf::Event &event) override;
	virtual void onUpdate() override;

private:
};