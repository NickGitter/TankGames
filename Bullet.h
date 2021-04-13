#pragma once
#include "Enemy.h"
#include <iostream>
#include "Player.h"
#include <cmath>
#define toGrad(a) a*3.1415/180


class Bullet :public Enemy
{
private:
	SDL_Point points[4];
public:
	void updatePoints() 
	{
		//добавленно
		int newX1, newY1, newX2, newY2, newX3, newY3, newX4, newY4;
		int cX = m_centerX + m_position.getX();
		int cY = m_centerY + m_position.getY();
		double angle = m_angle;
		int x1 = m_position.getX();
		int y1 = m_position.getY();
		int W = m_width;
		int H = m_height;
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 0, 0, 255);
		newXY(x1, y1, cX, cY, angle, newX1, newY1);
		newXY(x1 + W, y1, cX, cY, angle, newX2, newY2);
		newXY(x1 + W, y1 + H, cX, cY, angle, newX3, newY3);
		newXY(x1, y1 + H, cX, cY, angle, newX4, newY4);
		/*
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), newX1, newY1, newX2, newY2);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), newX2, newY2, newX3, newY3);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), newX3, newY3, newX4, newY4);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), newX4, newY4, newX1, newY1);
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
		*/
		points[0].x = newX1;
		points[0].y = newY1;
		points[1].x = newX2;
		points[1].y = newY2;
		points[2].x = newX3;
		points[2].y = newY3;
		points[3].x = newX4;
		points[3].y = newY4;
	}
	void load(LoaderParams *pParams)
	{
		Enemy::load(pParams);
	}
	void update()
	{
		double speed = 3;

		double preAngle = m_angle - 90;
		if (preAngle >= 360)
			preAngle -= 360;

		if (preAngle < 0)
			preAngle += 360;
		updatePoints();
		m_acceleration = Vector2D(-speed * sin(toGrad(preAngle)), speed * cos(toGrad(preAngle)));

		Enemy::update();
		
		//std::cout << "rotate Angle"<<this->getRotate() << std:: endl;
		//m_position.setX(m_position.getX() + 0.5);
	}
	void draw()
	{
		Enemy::draw(m_angle, m_centerX, m_centerY, m_marginX, m_marginY);
	}
	void clear()
	{
		Enemy::clear();
	}
	SDL_Point* getPoints() 
	{
		return &points[0];
	}
	Bullet() :Enemy() {};
	~Bullet() 
	{
	}
};