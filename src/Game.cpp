#include <PCH.hpp>
#include <Game.hpp>

Game::Game()
	: m_name(), m_pWindow(nullptr), m_pGameState(nullptr), m_isRunning(false), m_pFPSIndicator() {}

Game::Game(const std::string &name)
	: m_name(name), m_isRunning(true) {
	LOG_TRACE("Create game...");

	// Create and setup window
	m_pWindow = new sf::RenderWindow(sf::VideoMode(800, 600), name);
	m_pWindow->setVerticalSyncEnabled(true);

	// Create game state
	m_pGameState = new GameState(m_pWindow);

	// Initialize UI system
	UI::init();

	// Set default Scene
	m_mainMenu = new MainMenu(m_pGameState);
	m_pGameState->setScene(m_mainMenu);

	// Set FPS indicator
	m_pFPSIndicator = new sf::Text();
	m_pFPSIndicator->setFont(*UI::getDefaultFont());
	m_pFPSIndicator->setCharacterSize(12);
	m_pFPSIndicator->setPosition(0.0f, 0.0f);

	LOG_TRACE("Game created successfully.");
}

Game::~Game() {
	LOG_TRACE("Close game...");

	delete m_pFPSIndicator;
	UI::destroy();
	delete m_pGameState;

	LOG_TRACE("Game closed successfully.");
}

void Game::onUpdate() {
	m_pGameState->updateDeltaTime();
	m_pFPSIndicator->setString(std::to_string((int)(1.0f / m_pGameState->getDeltaTime())));

	// Clear window
	m_pWindow->clear();

	// Handle events
	sf::Event event;
	while (m_pWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_isRunning = false;
			m_pWindow->close();
		}
		if (m_pGameState->getScene()) {
			m_pGameState->getScene()->onEvent(event);
		}
		else {
			LOG_WARNING("Game State Scene not defined !");
		}
	}

	// Display current scene
	if (m_pGameState->getScene()) {
		m_pGameState->getScene()->onUpdate();
	}
	else {
		LOG_WARNING("Game State Scene not defined !");
	}

	// Display changes
	m_pWindow->draw(*m_pFPSIndicator);
	m_pWindow->display();
}

bool Game::isRunning() const {
	return m_isRunning;
}