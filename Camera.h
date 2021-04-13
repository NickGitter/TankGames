#pragma once
#include "vector2D.h"
#include "Game.h"
class Camera
{
private:
	Vector2D* m_pTarget;
	Vector2D m_position;
public:
	//void update(Vector2D velocity);
	void setTarget(Vector2D* target){ m_pTarget = target; }
	void setPosition(const Vector2D& position) { m_position = position; }
	Vector2D getPosition();
//SingleTon trick's
private:
	static Camera* s_pCamera;
	Camera() { m_pTarget = 0; }
public:
	static Camera* Instance() 
	{
		if (s_pCamera == 0) 
		{
			s_pCamera = new Camera();
		}
		return s_pCamera;
	}
	~Camera() {}
};
typedef Camera TheCamera;