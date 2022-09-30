#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
	TileMap();
	TileMap(const std::string &tileSet, sf::Vector2u tileSize, const int *tiles,
			unsigned int width, unsigned int height);

	bool load(const std::string &tileSet, sf::Vector2u tileSize,
			  const int *tiles, unsigned int width, unsigned int height);

private:
	sf::VertexArray m_vertices;
	sf::Texture m_tileSet;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // TILEMAP_H_
