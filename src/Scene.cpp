#include <PCH.hpp>
#include <Scene.hpp>

Scene::Scene()
	: m_pGameState(nullptr) {}

Scene::Scene(GameState *pGameState)
	: m_pGameState(pGameState) {}

Scene::~Scene() {}

void Scene::onUpdate() {}

void Scene::onEvent(sf::Event &event) {}