#pragma once
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"
#include <vector>
class TileLayer :public Layer {
public:
	TileLayer(int tileSize, const std::vector<Tileset> &tilesets);
	TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets);
	void setTileIDs(const std::vector<std::vector<int>>& data){
		m_tileIDs=data;
	}
	Vector2D getPosition() { return m_position; }
	virtual ~TileLayer(){}
	virtual void update();
	virtual void render();
	void setTileSize(int tileSize);
	void setTilesetByID(int tileID);
	Tileset getTilesetByID(int tileID);
private:
	Vector2D m_position,m_velocity;
	int m_numColumns;
	int m_numRows;
	int m_tileSize;
	int m_mapWidth;
	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};