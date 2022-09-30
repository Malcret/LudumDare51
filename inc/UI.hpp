#pragma once

#include <Core/Core.hpp>
#include <SFML/Graphics.hpp>

class UI {
public:
	UI();
	UI(sf::RenderWindow *pWindow);
	virtual ~UI();

	virtual void draw() = 0;

	void setWindow(sf::RenderWindow *pWindow);

	static void init();
	static void destroy();
	static const sf::Font *getDefaultFont();

protected:
	sf::RenderWindow *m_pWindow;

	static inline sf::Font *s_pNotoSans;
	static inline sf::Font *s_pDefaultFont;

private:
	static inline bool s_isInit = false;
};