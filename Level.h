#pragma once
#include <string>
#include <vector>
#include "Layer.h"
struct Tileset;
struct CollisionObject 
{
	std::string id, name;
	int x, y,width,height;
};
class Level {
public:
	void update();
	void render();
public: //херня с вектором
	std::vector<Tileset>* getTilesets() { return &m_tilesets;	}
	std::vector<Layer*>* getLayers()	{ return &m_layers;		}
	std::vector<CollisionObject>* getCollisions() { return &m_collisionObjects; }
public:
	friend class LevelParser;
	Level() {}
private:
	~Level() {}
private:
	std::vector<CollisionObject> m_collisionObjects;
	std::vector<Layer*> m_layers;
	std::vector<Tileset> m_tilesets;
};
struct Tileset{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};