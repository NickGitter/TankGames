#pragma once
#include "Enemy.h"
#include <iostream>
#include "InputHandler.h"
#include "Camera.h"

void newXY(int x1, int y1, int cX, int cY, double a, int &newX, int &newY);

class Player:public Enemy
{
public:
	virtual void load(LoaderParams *pParams)
	{
		Enemy::load(pParams);
	}
	virtual void update() 
	{
		Enemy::update();
	}
	virtual void draw() 
	{
		Enemy::draw();
	}
	virtual void clear() 
	{
		Enemy::clear();
	}
	Player() :Enemy() {};
	~Player() {}
};
class TankGun :public Enemy 
{
public:
	void load(LoaderParams *pParams) 
	{
		Enemy::load(pParams);
	}
	void update(Vector2D tankPosition);
	void update() 
	{

	}
	void draw() {
		Enemy::draw(m_angle,m_centerX,m_centerY,m_marginX,m_marginY);
	}
	void clear() {
		Enemy::clear();
	}
	TankGun() :Enemy() {}
	~TankGun() {}
	double getGunRotate() { return m_angle + 90; }
};
class Tank :public Enemy{
private:
	SDL_Point points[4];
	TankGun m_gun;
	void rotate();
	float speed =3.0f;
public:
	virtual double getGunRotate() {return m_gun.getGunRotate(); }
	void backStep();
	SDL_Point* getPoints() { return &points[0]; }
	void updatePoints();
	Vector2D getPosition() { return m_position; }
	void load(LoaderParams *pParams)
	{
		Enemy::load(pParams);
	}
	void load(LoaderParams *tankParams, LoaderParams *gunParams) 
	{
		Enemy::load(tankParams);
		m_gun.load(gunParams);
	}
	void update()
	{
		m_velocity.setX(0);
		m_velocity.setY(0);
		m_acceleration.setX(m_acceleration.getX() / 1.1);
		m_acceleration.setY(m_acceleration.getY() / 1.1);
		if (m_bCanRotate)
			rotate();
		else 
		{
			m_acceleration.setX(0);
			m_acceleration.setY(0);
		}
		Enemy::update();
		updatePoints();
		m_gun.update(getPosition());
	}
	void draw();
	void clear() 
	{
		Enemy::clear();
	}
	Tank() :Enemy() {}
	~Tank() {}

};