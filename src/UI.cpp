#include <PCH.hpp>
#include <UI.hpp>

UI::UI()
	: m_pWindow(nullptr) {}

UI::UI(sf::RenderWindow *pWindow)
	: m_pWindow(pWindow) {}

UI::~UI() {}

void UI::setWindow(sf::RenderWindow *pWindow) {
	m_pWindow = pWindow;
}

void UI::init() {
	LOG_TRACE("Initialize UI system...");

	s_pNotoSans = new sf::Font();
	ASSERT_MSG(s_pNotoSans->loadFromFile("resources/fonts/NotoSans-Regular.ttf"), "Failed to load font !");
	s_pDefaultFont = s_pNotoSans;

	LOG_TRACE("UI system initialized successfully.");
}

void UI::destroy() {
	LOG_TRACE("Destroy UI system...");

	delete s_pNotoSans;

	LOG_TRACE("UI system destroyed successfully.");
}

const sf::Font *UI::getDefaultFont() {
	return s_pDefaultFont;
}