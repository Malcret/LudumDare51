#include <TileMap.hpp>
#include <iostream>

TileMap::TileMap()
	: m_vertices(), m_tileSet() {}

TileMap::TileMap(const std::string &tileSet, sf::Vector2u tileSize,
				 const int *tiles, unsigned int width, unsigned int height) {
	if (!this->load(tileSet, tileSize, tiles, width, height)) {
		std::cerr << "Failed to create the tile map !\n";
	}
}

bool TileMap::load(const std::string &tileSet, sf::Vector2u tileSize,
				   const int *tiles, unsigned int width, unsigned int height) {
	// Load tile set texture
	if (!m_tileSet.loadFromFile(tileSet)) {
		return false;
	}

	// Set vertex array size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// Populate vertex array with proper tiles
	for (size_t i = 0; i < width; ++i) {
		for (size_t j = 0; j < height; ++j) {
			// Get tile ID
			int tileID = tiles[i + j * width];

			// Tile position in tile set
			int tu = tileID % (m_tileSet.getSize().x / tileSize.x);
			int tv = tileID / (m_tileSet.getSize().x / tileSize.x);

			// Get tile's quad
			sf::Vertex *quad = &m_vertices[(i + j * width) * 4];

			// Set quad position
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// Set quad texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}

	return true;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= this->getTransform();
	states.texture = &m_tileSet;
	target.draw(m_vertices, states);
}
