#pragma once

#include <Core/Core.hpp>
#include <SFML/Graphics.hpp>

class Scene;

class GameState {
public:
	GameState();
	GameState(sf::RenderWindow *pWindow);
	~GameState();

	void updateDeltaTime();

	void setScene(Scene *pScene);
	void setPause(bool pause);

	sf::RenderWindow *getWindow();
	Scene *getScene();
	sf::Clock &getClock();
	float getLastFrame();
	float getCurrentFrame();
	float getDeltaTime();
	bool getPause();

protected:
	sf::RenderWindow *m_pWindow;
	Scene *m_pScene = nullptr;
	sf::Clock m_clock;
	float m_lastFrame = 0.0f;
	float m_currentFrame = 0.0f;
	float m_deltaTime = 0.0f;
	bool m_pause = false;
};