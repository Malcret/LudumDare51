#pragma once

#include <Core/Core.hpp>
#include <GameState.hpp>
#include <UI.hpp>

class Scene {
public:
	Scene();
	Scene(GameState *pGameState);
	virtual ~Scene();

	virtual void onEvent(sf::Event &event);
	virtual void onUpdate();

protected:
	GameState *m_pGameState;
};