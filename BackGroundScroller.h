#pragma once
#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"
class BackGroundScroll:public Enemy 
{
private:
	int m_tick=0;
public:
	virtual void load(LoaderParams *pParams)
	{
		Enemy::load(pParams);
	}
	virtual void update()
	{
		m_tick += 2;
	}
	void draw()
	{
		int pos = TheCamera::Instance()->getPosition().getX();
		TheTextureManager::Instance()->drawBackGround(m_textureID, pos, TheGame::Instance()->getRenderer(),500);
	}
	virtual void clear()
	{
		Enemy::clear();
	}
	void changeBackGround(std::string _newID) 
	{
		m_textureID = _newID;
	}

/*Trick's for SingleTon*/
private:
	static BackGroundScroll* m_sInstance;
	BackGroundScroll() {}
public:
	~BackGroundScroll() {}
	static BackGroundScroll* Instance() 
	{
		if (m_sInstance == nullptr) 
		{
			m_sInstance = new BackGroundScroll();
		}
		return m_sInstance;
	}
};
typedef BackGroundScroll TheBackGroundScrolling;