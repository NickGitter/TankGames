#include "Camera.h"
Camera* Camera::s_pCamera=0;
 Vector2D Camera::getPosition()
{
	if (m_pTarget != 0) 
	{
		//return Vector2D(m_pTarget->getX(), m_pTarget->getY());
		Vector2D pos(m_pTarget->getX() - (TheGame::Instance()->getGameWidth() / 2), m_pTarget->getY() - (TheGame::Instance()->getGameHeight() / 2));
		if (pos.getX() < 0) 
		{
			pos.setX(0);
		}if (pos.getY() < 0)
		{
			pos.setY(0);
		}
		return pos;
	}
	return m_position;
}