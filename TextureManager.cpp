#include "TextureManager.h"
#include <iostream>
#include "Game.h"
#include "Camera.h"
TextureManager* TextureManager::s_pInstance = nullptr;
TextureManager* TextureManager::Instance() {
	if (s_pInstance == nullptr){
		s_pInstance = new TextureManager();
	}
	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id) {
	SDL_Surface* temp;
	temp = IMG_Load(fileName.c_str());
	if (temp == nullptr)
	{
		std::cout << SDL_GetError() << "\n";
		std::cout << "ÍÅ ÍÀÉÄÅÍÀ ÊÀÐÒÈÍÊÀ: " << fileName.c_str() << "\n";
		return false;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), temp);
	SDL_FreeSurface(temp);
	if (texture == nullptr)
	{
		std::cout << "ÕÇ Â ×ÅÌ ÏÐÎÁËÅÌÌÀ\n";
		return false;
	}
	m_textureMap[id] = texture;
	return true;
}

void TextureManager::drawBackGround(std::string id,int &tick, SDL_Renderer* pRenderer,int maxWidth)
{
	SDL_Rect srcRect, dstRect;
START:
	dstRect.x = 0;
	dstRect.y = 0;
	srcRect.w = dstRect.w = maxWidth;
	srcRect.h = dstRect.h = TheGame::Instance()->getGameHeight();
	
	srcRect.x = tick;
	srcRect.y = 0;
	dstRect.w -= tick;
	bool fl = true;
	do {
		if (dstRect.w == 0){
		}
		SDL_RenderCopy(pRenderer, m_textureMap[id], &srcRect, &dstRect);
		if ((dstRect.x + dstRect.w) < TheGame::Instance()->getGameWidth())
		{
			dstRect.x += dstRect.w;
			dstRect.w = maxWidth;
			srcRect.x = 0;
			srcRect.w = dstRect.w;
		}
		else
			fl = false;
	} while (fl);
}
void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentColl, int currentRow, SDL_Renderer* pRenderer, double angle, int centerX,int centerY,int alpha, SDL_RendererFlip flip) {
	SDL_Rect srcRect, dstRect;
	SDL_Point center;
	center.x = centerX;
	center.y = centerY;
	srcRect.x = width*	(currentColl);
	srcRect.y = height*	(currentRow);
	dstRect.x = x -TheCamera::Instance()->getPosition().getX();
	dstRect.y = y -TheCamera::Instance()->getPosition().getY();
	srcRect.h = dstRect.h = height;
	srcRect.w = dstRect.w = width;

	//SDL_SetTextureAlphaMod(m_textureMap[id], 113);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, angle, &center, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentColl, int currentRow, SDL_Renderer* pRenderer, double angle, int centerX, int centerY, int alpha,int marginX,int marginY, SDL_RendererFlip flip) {
	SDL_Rect srcRect, dstRect;
	SDL_Point center;
	center.x = centerX;
	center.y = centerY;
	srcRect.x = width*	(currentColl) + marginX;
	srcRect.y = height*	(currentRow) + marginY;
	dstRect.x = x - Camera::Instance()->getPosition().getX();
	dstRect.y = y + Camera::Instance()->getPosition().getY();
	srcRect.h = dstRect.h = height;
	srcRect.w = dstRect.w = width;

	//SDL_SetTextureAlphaMod(m_textureMap[id], 113);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, angle, &center, flip);
}
TextureManager::TextureManager(){
}
TextureManager::~TextureManager(){
}
void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width)*currentFrame;
	srcRect.y = margin + (spacing + height)*currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}