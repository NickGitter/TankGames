#include "Player.h"
#include "Game.h"
#include "Collision.h"
#define toGrad(a) a*3.1415/180
//функция вращения точки вокруг точки
void newXY(int x1, int y1, int cX, int cY, double a, int &newX, int &newY)
{
	newX = cX + (x1 - cX) * cos(toGrad(a)) - (y1 - cY)*sin(toGrad(a));
	newY = cY + (y1 - cY) * cos(toGrad(a)) + (x1 - cX)*sin(toGrad(a));
}
void Tank::updatePoints()
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
	//
}
void Tank::draw() 
{
		Enemy::draw(m_angle, m_centerX, m_centerY, m_marginX, m_marginY);
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 0, 0, 0, 255);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), points[0].x, points[0].y, points[1].x, points[1].y);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), points[1].x, points[1].y, points[2].x, points[2].y);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), points[2].x, points[2].y, points[3].x, points[3].y);
		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(), points[3].x, points[3].y, points[0].x, points[0].y);

		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 128, 64, 32, 255);

		
			int offer = 5;
			SDL_Rect r;
			SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 127, 63, 31, 255);
			r.x = points[0].x - offer;
			r.y = points[0].y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &r);
			r.x = points[1].x - offer;
			r.y = points[1].y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &r);
			SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 31, 63, 127, 255);
			r.x = points[2].x - offer;
			r.y = points[2].y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &r);
			r.x = points[3].x - offer;
			r.y = points[3].y - offer;
			r.w = offer * 2;
			r.h = offer * 2;
			SDL_RenderDrawRect(TheGame::Instance()->getRenderer(), &r);

		m_gun.draw();
}
void TankGun::update(Vector2D tankPosition)  
{
		
		m_position = tankPosition + Vector2D(5, 1);
		SDL_Point p;
		p.x = m_position.getX() + m_width / 2 - (int)(TheCamera::Instance()->getPosition().getX());
		p.y = m_position.getY() + m_height / 2 - (int)(TheCamera::Instance()->getPosition().getY());
		int mouseX = InputHandler::Instance()->getMousePosition()->getX();
		int mouseY = InputHandler::Instance()->getMousePosition()->getY();
		int NmouseX = mouseX - p.x;
		int NmouseY = mouseY - p.y;
		double c = sqrt(NmouseX*NmouseX + NmouseY*NmouseY);
		bool fl = true;
		double angle;
		if (NmouseY / c >= 0)
			angle = asin(NmouseY / c) * 180 / 3.1415;
		else {
			angle = asin(-NmouseY / c) * 180 / 3.1415;
			fl = false;
		}
		if (mouseX < p.x)
			if (mouseY > p.y)
				m_angle = 180 - angle;
			else
				m_angle = angle + 180;
		else
			if (mouseY > p.y)
				m_angle = angle;
			else
				m_angle = -angle;
		m_angle -= 90;

}
void Tank::backStep() 
{
	Enemy::backStep();
	m_angle			= m_backAngle;
	m_position		= m_backPosition;
	m_acceleration	= m_backAcceleration;
	m_velocity		= m_backVelocity;
	updatePoints();
}
void Tank::rotate() 
{
	double prevAngle = m_angle;
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) 
	{
		m_angle += 3;
		if (m_angle >= 360)
			m_angle -= 360;
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) 
	{
		m_angle -= 3;
		if (m_angle  < 0)
			m_angle += 360;
	}
	updatePoints();
	/*if (CollisionManager::Instance()->checkCollisionwithSolid2(this,points, 4, TheGame::Instance()->getCollisions())) 
	{
		m_angle = prevAngle;
		updatePoints();
	}
	*/
	if (CollisionManager::Instance()->checkCollisionwithSolid2(this,points, 4, TheGame::Instance()->getCollisions()))
	{
		m_angle = prevAngle;
		updatePoints();
	}
	
	Vector2D prevAcceleration = m_acceleration;
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
		speed = 6.0;
	else
		speed = 3.0;

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) 
	{
		m_acceleration = Vector2D(speed * sin(toGrad(m_angle)), -speed * cos(toGrad(m_angle)));
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) 
	{
		m_acceleration = Vector2D(-speed * sin(toGrad(m_angle)), speed * cos(toGrad(m_angle)));
	}
}