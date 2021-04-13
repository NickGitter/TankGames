#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"
Level* LevelParser::parseLevel(const char* levelFile) 
{
	TiXmlDocument levelDocument;
	if (!levelDocument.LoadFile(levelFile)) 
	{
		std::cout << "ÎØÈÁÊÀ ÎÒÊÐÛÒÈß ÔÀÉËÀ: "<<levelFile<<"\n";
		return nullptr;
	}
	Level* pLevel = new Level();
	TiXmlElement* pRoot = levelDocument.RootElement();
	pRoot->Attribute("tilewidth",	&m_tileSize	);
	pRoot->Attribute("width"	,	&m_width	);
	pRoot->Attribute("height"	,	&m_height	);

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) 
	{
		if (e->Value() == std::string("layer")) 
		{
			parseTileLayer(e, pLevel->getLayers(),pLevel->getTilesets());
		}
	}

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup"))
		{
			if (e->Attribute("name") == std::string("SOLID"))
			{
				parseColisionObjects(e, pLevel->getCollisions());
			}
		}
	}
	return pLevel;
}
void LevelParser::parseColisionObjects(TiXmlElement* pTilesetRoot, std::vector<CollisionObject>* pCollisionObjects)
{
	for (TiXmlElement* e = pTilesetRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		CollisionObject t;
		t.id = e->Attribute("id");
		t.name = e->Attribute("name");
		e->Attribute("width", &t.width);
		e->Attribute("height", &t.height);
		e->Attribute("x", &t.x);
		e->Attribute("y", &t.y);
		std::cout << "t.x= " << t.x << " t.id " << t.id << "\n";
		pCollisionObjects->push_back(t);
	}
}
void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets) 
{
	TextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"));
	Tileset tileset;
	tileset.spacing = tileset.margin=0;
	pTilesetRoot->Attribute("firstgid"						, &tileset.firstGridID	);
	pTilesetRoot->FirstChildElement()->Attribute("width"	, &tileset.width		);
	pTilesetRoot->FirstChildElement()->Attribute("height"	, &tileset.height		);
	pTilesetRoot->Attribute("tilewidth"						, &tileset.tileWidth	);
	pTilesetRoot->Attribute("tileheight"					, &tileset.tileHeight	);
	pTilesetRoot->Attribute("spacing"						, &tileset.spacing		);
	pTilesetRoot->Attribute("margin"						, &tileset.margin		);
	tileset.name = pTilesetRoot->Attribute("name");
	if ((tileset.tileWidth + tileset.spacing)!=0)
		tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
	pTilesets->push_back(tileset);
}
void LevelParser::parseTileLayer(TiXmlElement* pTileElement,
	std::vector<Layer*> *pLayers, const std::vector<Tileset>*
	pTilesets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	// tile data
	std::vector<std::vector<int>> data;
	std::string decodedIDs;
	int *t = new int[m_width*m_height];
	TiXmlElement* pDataNode;
	int k = 0;
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}
	for (TiXmlElement* e = pDataNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		e->Attribute("gid",&t[k++]);
	}
	/*for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::cout<<"e->attribute(\"grid\")"
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}*/
	// uncompress zlib compression
//	uLongf numGids = m_width * m_height * sizeof(int);
//	std::vector<unsigned> gids(numGids);
//	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)t, decodedIDs.size());
	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = t[rows*m_width + cols];
		}
	}

	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);
}