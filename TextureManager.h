#pragma once
#include <SDL_image.h>
#include <map>
class TextureManager
{
public:
	bool load(std::string fileName, std::string id);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentColl, int currentRow, SDL_Renderer* pRenderer, double angle, int centerX, int centerY, int alpha, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentColl, int currentRow, SDL_Renderer* pRenderer, double angle, int centerX, int centerY, int alpha, int marginX, int marginY, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);
	void clearFromTextureMap(std::string id) { m_textureMap.erase(id); }
	
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	
	void drawBackGround(std::string id,int &tick, SDL_Renderer* pRenderer,int maxWidth);


private:
	std::map<std::string, SDL_Texture*> m_textureMap;

//Trick's for SingleTon
private:
	static TextureManager* s_pInstance;
	TextureManager();
public:
	static TextureManager* Instance();
	~TextureManager();
};
typedef TextureManager TheTextureManager;