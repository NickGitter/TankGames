#pragma once
#include <tinyxml.h>
#include <tinystr.h>
#include "Level.h"
class LevelParser {
public:
	Level* parseLevel(const char* levelFIle);
private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);
	void parseColisionObjects(TiXmlElement* pTilesetRoot, std::vector<CollisionObject>* pCollisionObjects);
private:
	int m_tileSize;
	int m_width, m_height;
};