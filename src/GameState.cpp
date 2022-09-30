#include <PCH.hpp>
#include <GameState.hpp>

GameState::GameState()
	: m_pWindow(nullptr), m_pScene(nullptr) {}

GameState::GameState(sf::RenderWindow *pWindow)
	: m_pWindow(pWindow), m_pScene(nullptr) {}

GameState::~GameState() {}

void GameState::updateDeltaTime() {
	this->m_currentFrame = this->m_clock.getElapsedTime().asSeconds();
	this->m_deltaTime = this->m_currentFrame - this->m_lastFrame;
	this->m_lastFrame = this->m_currentFrame;
}

void GameState::setScene(Scene *pScene) {
	m_pScene = pScene;
}

void GameState::setPause(bool pause) {
	m_pause = pause;
}

sf::RenderWindow *GameState::getWindow() {
	return m_pWindow;
}

Scene *GameState::getScene() {
	return m_pScene;
}

sf::Clock &GameState::getClock() {
	return m_clock;
}

float GameState::getLastFrame() {
	return m_lastFrame;
}

float GameState::getCurrentFrame() {
	return m_currentFrame;
}

float GameState::getDeltaTime() {
	return m_deltaTime;
}

bool GameState::getPause() {
	return m_pause;
}