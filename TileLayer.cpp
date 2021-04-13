#include "TileLayer.h"
#include "Game.h"
#include "Camera.h"
#include "TextureManager.h"
#include <iostream>
TileLayer::TileLayer(int tileSize,const std::vector<Tileset>& tilesets):m_tileSize(tileSize),m_tilesets(tilesets),m_position(0,0),m_velocity(0,0) 
{
	m_numColumns = (Game::Instance()->getGameWidth() / m_tileSize);
	m_numRows = (Game::Instance()->getGameHeight() / m_tileSize);
}
TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight,
	const std::vector<Tileset>& tilesets) : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;
	m_mapWidth = mapWidth;
}
void TileLayer::update() 
{
	//m_position = TheCamera::Instance()->getPosition();
	m_velocity.setX(1); m_position += m_velocity;
	
}
void TileLayer::render() 
{
	//TheCamera::Instance()->setPosition(Vector2D(0, 0));
	int x, y, x2, y2 = 0;
	m_position = TheCamera::Instance()->getPosition();
	x	= m_position.getX()/ m_tileSize;
	y	= m_position.getY()/ m_tileSize;
	x2	= int(m_position.getX()) % m_tileSize;
	y2	= int(m_position.getY()) % m_tileSize;
	int newX, newY;


	for (int i = 0; i < m_numRows; ++i)
	{
		for (int j = 0; j < m_numColumns+1; ++j)
		{
			int id = m_tileIDs[ i ][ j + TheCamera::Instance()->getPosition().getX() / m_tileSize];
			if (id == 0) continue;
			if (((((j*m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX()) < -m_tileSize) || (((j*m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX()) > Game::Instance()->getGameWidth())
			{
				//std::cout << "continue" << "\n";
			}
			Tileset tileset = getTilesetByID(id);
			--id;
			newX = j*m_tileSize;
			newY = i*m_tileSize;
			TextureManager::Instance()->drawTile
			(
				tileset.name,
				tileset.margin, tileset.spacing,
				newX - (int)(TheCamera::Instance()->getPosition().getX()) % m_tileSize,
				newY - (int)(TheCamera::Instance()->getPosition().getY()) % m_tileSize,
				m_tileSize, m_tileSize,
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, 
				Game::Instance()->getRenderer()
			);

		}
	}

	/*
	for (int i = 0; i < m_numRows; ++i) 
	{
		for (int j = 0; j < m_numColumns; ++j)
		{
			int id = m_tileIDs[i+y][j + x];
			if (id == 0) continue;
			if (((((j*m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX()) < -m_tileSize) || (((j*m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX()) > Game::Instance()->getGameWidth())
			{
				std::cout << "continue" << "\n";
				//continue;
			}

			Tileset tileset = getTilesetByID(id);
			--id;
			if (tileset.numColumns == 0) continue;
			TextureManager::Instance()->drawTile
			(
				tileset.name,
				tileset.margin, tileset.spacing,
				((j * m_tileSize) - x2) - TheCamera::Instance()->getPosition().getX(),
				((i * m_tileSize) - y2) - TheCamera::Instance()->getPosition().getY(),
				m_tileSize, m_tileSize, 
				(id - (tileset.firstGridID - 1)) / tileset.numColumns,
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, Game::Instance()->getRenderer()
			);
		}
	}*/
}
Tileset TileLayer::getTilesetByID(int tileID) 
{
	for (int i = 0; i < m_tilesets.size(); ++i) 
	{
		if ((i + 1) <= (m_tilesets.size() - 1)) 
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID) 
			{
				return m_tilesets[i];
			}
		}
		else 
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did no find tileset with ID: "<<tileID<<", returning empty tileset";
	Tileset t;
	return t;
}