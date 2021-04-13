#pragma once
#include <SDL.h>
#include <iostream>
#include "InputHandler.h"
#include "Player.h"
#include "Level.h"
const int FPS = 30;
const int DELAY_TIME = 1000 / FPS;
class Game
{
private:
	Level *l;
	Enemy	*m_pPlayer;
	int		m_width, m_height;
	bool	m_bRunning;
	SDL_Window			*m_pWindow;
	SDL_Renderer		*m_pRenderer;
	bool initAllTextures();
	bool m_bDebugMode;
public:
	std::vector<CollisionObject> getCollisions() { return *l->getCollisions(); }
	int getGameWidth()		{ return m_width;	}
	int getGameHeight()		{ return m_height;	}
	bool init(const char* title, int xpos, int ypos, int width, int heigh, int flags);
	SDL_Renderer			*getRenderer() const { return m_pRenderer; }
	void quit();				// просто меняем флаг m_bRunning
	void handleEvents();		// ввод данных пользователя
	void update();				// обновление состояния системы
	void render();				// отрисовка
	void clean();				// удаление
	void run();					// запуск цикла игры
//Trick's for SingleTon
private:
	static Game* m_pGame;
	Game();
public:
	static Game* Instance();
	~Game();
};


typedef Game TheGame;