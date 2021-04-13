#pragma once
#include "Enemy.h"
#include "Player.h"
#include <math.h>
const double EXP = 0.09;
#define DoubleABS(x){ x>0?x:-x;}
class CollisionManager
{
private:
		SDL_Point m_pP1, m_pP2, m_pP3;
		bool m_bNeedToDrawPixels;
private:
	bool getValueFromFuncWithTwoPoints(SDL_Point p1,SDL_Point p2,SDL_Point p) 
	{
		if (((p2.x - p1.x == 0)) || ((p2.y - p1.y) == 0))
			return false;
		//std::cout << "p1:(" << p1.x << "," << p1.y << ") p2:(" << p2.x << "," << p2.y << ") " << " p:(" << p.x << "," << p.y << ")"<<std::endl;
		//system("pause");

		float a = p.x - p1.x;
		float b = p2.x - p1.x;
		float c = p.y - p1.y;
		float d = p2.y - p1.y;
		if (fabs((a / b) - (c / d))<=EXP) return true;
		else return false;
		if (((p.x - p1.x) / float((p2.x - p1.x))) == ((p.y - p1.y) / float((p2.y - p1.y)))) return true;
			return false;
		
		if (fabs(((p.x - p1.x) / (p2.x - p1.x)) - ((p.y - p1.y) / (p2.y - p1.y))) <= EXP) return true;
		else
			return false;
	}
	bool arePointsBetweenTwoPoints(SDL_Point p1, SDL_Point p2, SDL_Point p) 
	{
		p2.y = p2.y;
		p1.y = p1.y;
		p.y = p.y;
		if (getValueFromFuncWithTwoPoints(p1, p2, p) == false)
			return false;
		m_bNeedToDrawPixels = false;
		if (((p.x > p1.x) && (p.x < p2.x)) || ((p.x < p1.x) && (p.x > p2.x))) 
		{
			std::cout << "p1:(" << p1.x << "," << p1.y << ") p2:(" << p2.x << "," << p2.y << ") " << " p:(" << p.x << "," << p.y << ")" << std::endl;
			std::cout << ((p.x - p1.x) / (p2.x - p1.x)) - ((p.y - p1.y) / (p2.y - p1.y)) << std::endl;
			std::cout << fabs(((p.x - p1.x) / float(p2.x - p1.x)) - ((p.y - p1.y) / float(p2.y - p1.y)))<<std::endl;
			m_pP1 = p;
			m_pP2 = p1;
			m_pP3 = p2;
			m_bNeedToDrawPixels = true;
			return true;
		}
		else return false;
	}
public:
	void drawCollision(const std::vector<CollisionObject> &objects,SDL_Renderer * pRender) 
	{
		SDL_SetRenderDrawColor(pRender, 0, 0, 0, 0);
		for (int i = 0; i < objects.size(); ++i) 
		{
			SDL_RenderDrawLine(pRender, objects[i].x, objects[i].y, objects[i].x + objects[i].width, objects[i].y);
			SDL_RenderDrawLine(pRender, objects[i].x + objects[i].width, objects[i].y, objects[i].x + objects[i].width, objects[i].y+objects[i].height);
			SDL_RenderDrawLine(pRender, objects[i].x + objects[i].width, objects[i].y + objects[i].height, objects[i].x, objects[i].y + objects[i].height);
			SDL_RenderDrawLine(pRender, objects[i].x, objects[i].y + objects[i].height, objects[i].x, objects[i].y);
		}
		if (m_bNeedToDrawPixels) 
		{
			int offer = 5;
			SDL_Rect r;
			SDL_SetRenderDrawColor(pRender, 0, 255, 0, 0);
			r.x = m_pP1.x - offer;
			r.y = m_pP1.y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(pRender, &r);
			SDL_SetRenderDrawColor(pRender, 0, 0, 255, 0);
			r.x = m_pP2.x - offer;
			r.y = m_pP2.y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(pRender, &r);
			r.x = m_pP3.x - offer;
			r.y = m_pP3.y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(pRender, &r);
		}
		SDL_SetRenderDrawColor(pRender, 255, 0, 0, 0);

	}
	void CollisionManager::checkCollisionwithSolid(Enemy* pPlayer, const std::vector<CollisionObject> &objects)
	{
		int pX = pPlayer->getPosition()->getX();
		int pY = pPlayer->getPosition()->getY();
		int pW = pPlayer->getWidth();
		int pH = pPlayer->getHeight();


		for (int i = 0; i < objects.size(); ++i)
		{
			if
				(
					(((pX + pW) >= objects[i].x) && (pX <= (objects[i].x + objects[i].width)))
					&&
					(((pY + pH) >= objects[i].y) && (pY <= (objects[i].y + objects[i].height)))
				)
			{
				pPlayer->getPosition()->setX( pPlayer->getPosition()->getX()- pPlayer->getVelocity().getX());
				std::cout << "ÓÃÎË: "<<pPlayer->getRotate()<<" ÑÒÎËÊÍÎÂÅÍÈÅ Ñ ÎÁÚÅÊÒÎÌ : " << objects[i].id << "x: " << objects[i].x << " y: "<< objects[i].y << " w: "<< objects[i].width << " h: "<< objects[i].height << "\n";
				pPlayer->getPosition()->setY( pPlayer->getPosition()->getY()- pPlayer->getVelocity().getY());
			}
		}
	}
	bool collision(SDL_Point point, CollisionObject objects)
	{
		int pX = point.x;
		int pY = point.y;
		if (
			((pX >= objects.x) && (pX <= (objects.x + objects.width)))
									&&
			((pY >= objects.y) && (pY <= (objects.y + objects.height)))
		)
			return true;
		else
			return false;

	}
	bool collision(CollisionObject object, SDL_Point *points) 
	{
		SDL_Point p;
		p.x = object.x;
		p.y = object.y;
		CollisionObject Cb;
		Cb.x = points[0].x;
		Cb.y = points[0].y;
		Cb.width = points[2].x - points[0].x;
		Cb.height = points[1].y - points[0].y;
		SDL_Point p2[4];
		p2[0].x = object.x;
		p2[0].y = object.y;
		p2[1].x = object.x + object.width;
		p2[1].y = object.y;
		p2[2].x = object.x + object.width;
		p2[2].y = object.y + object.height;
		p2[3].x = object.x;
		p2[3].y = object.y + object.height;;
		if (collision(points[0], object) || collision(points[1], object) || collision(points[2], object) || collision(points[3], object))
			return true;
		
		if (collision(p2[0], Cb) || collision(p2[1], Cb) || collision(p2[2], Cb) || collision(p2[3], Cb))
			return true;
		

		if (arePointsBetweenTwoPoints(points[0], points[1], p))
			return true;
		if (arePointsBetweenTwoPoints(points[2], points[3], p))
			return true;

		p.x = object.x + object.width;
		if (arePointsBetweenTwoPoints(points[0], points[1], p))
			return true;
		if (arePointsBetweenTwoPoints(points[2], points[3], p))
			return true;
		p.y = object.y + object.height;
		if (arePointsBetweenTwoPoints(points[0], points[1], p))
			return true;
		if (arePointsBetweenTwoPoints(points[2], points[3], p))
			return true;
		p.x = object.x;
		if (arePointsBetweenTwoPoints(points[0], points[1], p))
			return true;
		if (arePointsBetweenTwoPoints(points[2], points[3], p))
			return true;
		return false;
	}
	bool collisionPlayerObjects(Enemy* p, CollisionObject o) 
	{
		int px = p->getPosition()->getX();
		int py = p->getPosition()->getY();
		int pw = p->getWidth();
		int ph = p->getHeight();
		if
			(
				(((px + pw) >= o.x) && (o.x<px))
				&&
				(((py + ph) >= o.y) && (py>o.y))
				) return true;
		return false;
	}
	bool CollisionManager::checkCollisionwithSolid(SDL_Point* points, const int pointsCount,const std::vector<CollisionObject> &objects)
	{
		for (int i = 0; i < objects.size(); ++i)
		{
			for (int j = 0; j < pointsCount; ++j)
				if(collision(points[j], objects[i]))
				{
					return true;
				}
		}
		return false;
	}
	bool CollisionManager::checkCollisionwithSolid2(Enemy* pPlayer, SDL_Point* points, const int pointsCount, const std::vector<CollisionObject> &objects)
	{
		for (int i = 0; i < objects.size(); ++i)
		{
			if (collision(objects[i], points)) 
				return true;
			for (int j = 0; j < pointsCount; ++j) 
				if (collision(points[j], objects[i]))
					return true;
		}
		return false;
	}
private:
	CollisionManager():m_bNeedToDrawPixels(false) {}
	static CollisionManager* s_pInstance;
public:
	static CollisionManager* Instance();
	~CollisionManager() {}
};