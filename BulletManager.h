#pragma once
#include "Bullet.h"
#include "Player.h"
#include "Collision.h"
#include "Camera.h"
#include <vector>
class BulletManager 
{
private:
	static BulletManager * m_sInstance;
	BulletManager() {}
public:
	~BulletManager() {}
	static BulletManager* Instance() 
	{
		if (m_sInstance == nullptr) 
		{
			m_sInstance = new BulletManager();
		}
		return m_sInstance;
	}
private:
	std::vector<Bullet*> m_arrPlayerBullets;
	std::vector<Bullet*> m_arrEnemyBullets;
public:
	std::vector<Bullet*>* getPlayerBulletsVector() 
	{
		return &m_arrPlayerBullets;
	}
	std::vector<Bullet*>* getEnemyBulletsVector()
	{
		return &m_arrEnemyBullets;
	}
	void AddPlayerBullet(Tank* p) 
	{
		Bullet* b = new Bullet();
		b->load(new LoaderParams("bullet", p->getPosition().getX(), p->getPosition().getY(), 59, 33, 1, 1,0,0,p->getGunRotate(),30,16));
		m_arrPlayerBullets.push_back(b);
	}
	void update() 
	{
		for (int i = 0; i < m_arrPlayerBullets.size(); ++i) 
		{
			m_arrPlayerBullets[i]->update();
		}
		for (int i = 0; i < m_arrEnemyBullets.size(); ++i)
		{
			m_arrEnemyBullets[i]->update();
		}
		std::vector<Bullet*>::iterator i_reserv = m_arrPlayerBullets.begin();
		std::vector<CollisionObject> t = TheGame::Instance()->getCollisions();
		for (std::vector<Bullet*>::iterator i = m_arrPlayerBullets.begin(); i != m_arrPlayerBullets.end();)
		{
			bool fl = true;
			for (int i2 = 0; i2 < t.size() && fl; ++i2)
				if (CollisionManager::Instance()->collision(t[i2], (*i)->getPoints()))
				{
					i = m_arrPlayerBullets.erase(i);
					fl = false;
				}
			if (fl)
				++i;
		}
		for (std::vector<Bullet*>::iterator i = m_arrPlayerBullets.begin(); i != m_arrPlayerBullets.end(); ) 
		{
			bool fl = true;
			if ((*i)->getPosition()->getX() > TheGame::Instance()->getGameWidth() || (*i)->getPosition()->getY() > TheGame::Instance()->getGameHeight())
			{
				i = m_arrPlayerBullets.erase(i);
			}
			else
				++i;
		}
	}
	void draw() 
	{
		for (int i = 0; i < m_arrPlayerBullets.size(); ++i)
		{
			m_arrPlayerBullets[i]->draw();
		}
		for (int i = 0; i < m_arrEnemyBullets.size(); ++i)
		{
			m_arrEnemyBullets[i]->draw();
		}
	}
	void clearAllBullet() 
	{
		m_arrPlayerBullets.clear();
		m_arrEnemyBullets.clear();
	}
};
typedef BulletManager TheBulletManager;