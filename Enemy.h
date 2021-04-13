#pragma once
#include <string>
#include "vector2D.h"
#include <SDL.h>
class LoaderParams {
public:
	int m_x, m_y, m_width, m_height;						// данные текстуры
	int m_marginX, m_marginY;
	std::string m_textureID;								// ID текстуры
	int m_collCount, m_rowCount,m_centerX,m_centerY;
	double m_angle;
	LoaderParams(std::string textureID,int x, int y, int width, int height,int rowCount,int collCount,int marginX=0,int marginY=0,double angle = 0,int centerX = 0,int centerY = 0):m_textureID(textureID),m_x(x),m_y(y),m_width(width),m_height(height),m_collCount(collCount),m_rowCount(rowCount),m_angle(angle),m_centerX(centerX),m_centerY(centerY),m_marginX(marginX),m_marginY(marginY) {}
};
class Enemy
{
protected:
	Vector2D m_backVelocity, m_backAcceleration, m_backPosition;
	double m_backAngle;
protected:									// для текстуры
	bool m_bCanRotate;
	int m_width,m_height;						// данные текстуры
	int m_marginX, m_marginY;
	std::string m_textureID;							// ID текстуры
	int m_collCount, m_rowCount, m_currentColl, m_currentRow;
	double	m_angle;
	int		m_centerX, m_centerY;
protected:									// положение в пространстве
	Vector2D m_velocity, m_acceleration, m_position;	// позиция персонажа
public:
	void saveStep();
	void updateStep();
	virtual void backStep();
	virtual SDL_Point* getPoints() { return 0; }
	virtual void setRotate(bool canRotate) { m_bCanRotate = canRotate; }
	double getRotate() { return m_angle; }
	virtual double getGunRotate() { return 52; }
	Vector2D* getPosition() { return &m_position; }
	Vector2D getVelocity() { return m_velocity; }
	virtual int getWidth() { return m_width; }
	virtual int getHeight() { return m_height; }
	virtual void load(LoaderParams *pParams);
	virtual void load(LoaderParams *tankParams,LoaderParams* gunParams);
	virtual void update();
	virtual void draw();
	virtual void draw(double angle,int centerX,int centerY,int marginX=0,int marginY=0);
	virtual void clear();
	Enemy():m_width(0),m_height(0),m_currentColl(0),m_currentRow(0),m_collCount(0),m_rowCount(0),m_bCanRotate(true){	
	}
	~Enemy() {}
};

