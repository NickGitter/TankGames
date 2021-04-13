#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"
void Enemy::load(LoaderParams *pParams) {
	m_position.setX(pParams->m_x);
	m_position.setY(pParams->m_y);
	m_collCount = pParams->m_collCount;
	m_rowCount = pParams->m_rowCount;
	m_height = pParams->m_height;
	m_width = pParams->m_width;
	m_textureID = pParams->m_textureID;
	m_currentColl = 0;
	m_currentRow = 0;
	m_angle		= pParams->m_angle;
	m_centerX	= pParams->m_centerX;
	m_centerY	= pParams->m_centerY;
	m_marginX	= pParams->m_marginX;
	m_marginY	= pParams->m_marginY;
}

void Enemy::saveStep() 
{
	m_backPosition = m_position;
	m_backAcceleration = m_acceleration;
	m_backVelocity = m_velocity;
	m_backAngle = m_angle;
}
void Enemy::updateStep() {
}
void Enemy::backStep() 
{
	m_position = m_backPosition;
	m_acceleration = m_backAcceleration;
	m_velocity = m_backVelocity;
	m_angle = m_backAngle;
}
void Enemy::load(LoaderParams *tankParams, LoaderParams* gunParams) 
{
}
void Enemy::update() 
{
	saveStep();
	m_currentColl= int((SDL_GetTicks() / 100) % m_collCount);
	m_velocity += m_acceleration;
	m_position += m_velocity;
}
void Enemy::draw() 
{
	TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentColl, m_currentRow, TheGame::Instance()->getRenderer(), 0, 0, 0, 0);
}
void Enemy::draw(double angle, int centerX, int centerY, int marginX , int marginY ) 
{
	TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentColl, m_currentRow, TheGame::Instance()->getRenderer(), angle, centerX, centerY,0, marginX,m_marginY);
}
void Enemy::clear() 
{
	TheTextureManager::Instance()->clearFromTextureMap(m_textureID);
}