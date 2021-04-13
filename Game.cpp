#include "Game.h"
#include "TextureManager.h"
#include "Level.h"
#include "LevelParser.h"
#include "Camera.h"
#include "Collision.h"
#include "BulletManager.h"
#include "BackGroundScroller.h"
Game* Game::m_pGame = nullptr;
Game* Game::Instance() 
{
	if (m_pGame == nullptr)
		m_pGame = new Game;
	return m_pGame;
}
bool Game::init(const char* title, int xpos, int ypos, int width, int heigh, int flags) 
{
	m_width = width;
	m_height = heigh;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cout << "ÎØÈÁÊÀ ÏÎÄÊËÞ×ÅÍÈß SDL\n";
		return false;
	}
	m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, heigh, flags);
	if (m_pWindow == nullptr)
	{
		std::cout << "ÎØÈÁÊÀ ÑÎÇÄÀÍÈß ÎÊÍÀ\n";
		return false;
	}
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);//-1: ïåðâûé ñâîáîäíûé ÂÈÄÅÎÄÐÀÉÂÅÐ
	if (m_pRenderer == nullptr)
	{
		std::cout << "ÎØÈÁÊÀ ÑÎÇÄÀÍÈß ÐÅÍÄÅÐÀ\n";
		return false;
	}
	else
	{
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 225);
	}
	//m_pPlayer = new Player();
	//m_pPlayer->load(new LoaderParams("tank", 50, 50, 750 / 15, 500 / 6, 5, 16));

	m_pPlayer = new Tank();
	m_pPlayer->load(new LoaderParams("tank", 50, 50, 50, 72, 1, 1,0,0,0,25,25), new LoaderParams("tank", 55, 50, 40, 72, 1, 1,51,0,0,20,25));
	
	initAllTextures();
	if (!TheTextureManager::Instance()->load("textures/rezult.png", "tank")) 
	{
		std::cout << "Îøèáêà çàãðóçêè òåêñòóðû" << std::endl;
	}
	else 
	{
		std::cout << "Òåêñòóðà çàãðóæåííà" << std::endl;
	}
	return true;
}

bool Game::initAllTextures() 
{
	if (!TextureManager::Instance()->load("textures\\BULLET.png", "bullet")) 
	{
		std::cout << "Íå óäàëîñü çàãðóçèòü òåêñòóðó textures\\BULLET.png" << std::endl;
		return false;
	}
	if (!TextureManager::Instance()->load("textures\\bg.png", "backGround")) 
	{
		std::cout << "Íå óäàëîñü çàãðóçèòü òåêñòóðó textures\\bg.png" << std::endl;
		return false;
	}
	TheBackGroundScrolling::Instance()->changeBackGround("backGround");


	return true;
}
void Game::render() 
{
	SDL_RenderClear(m_pRenderer);
	TheBackGroundScrolling::Instance()->draw();
	l->render();
	m_pPlayer->draw();
	CollisionManager::Instance()->drawCollision(getCollisions(), m_pRenderer);
	TheBulletManager::Instance()->draw();
	//SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 255);
	SDL_RenderPresent(m_pRenderer);
}
void Game::update() 
{
	TheInputHandler::Instance()->update();
	TheBulletManager::Instance()->update();
	TheBackGroundScrolling::Instance()->update();
	m_pPlayer->update();
	//CollisionManager::Instance()->checkCollisionwithSolid(m_pPlayer, *l->getCollisions());
	//CollisionManager::Instance()->checkCollisionwithSolid(m_pPlayer->getPoints(), 4, *l->getCollisions());
	
	if (CollisionManager::Instance()->checkCollisionwithSolid2(m_pPlayer, m_pPlayer->getPoints(), 4, *l->getCollisions()) == true)
	{
		m_pPlayer->backStep();
		//m_pPlayer->getPosition()->setX(m_pPlayer->getPosition()->getX() - m_pPlayer->getVelocity().getX());
		//m_pPlayer->getPosition()->setY(m_pPlayer->getPosition()->getY() - m_pPlayer->getVelocity().getY());
		std::cout << "WORK\n";
	}
	if (TheInputHandler::Instance()->getMouseButtonState(0) == 1) 
	{
		BulletManager::Instance()->AddPlayerBullet(dynamic_cast<Tank*>(m_pPlayer));
		std::cout << "FIRE\n";
	}
}
void Game::handleEvents() 
{
	
}
void Game::clean() 
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
void Game::run() 
{
	int startTime,waitTime;
	
	LevelParser lParser;
	l = lParser.parseLevel("Levels\\TestLevel(1).tmx");
	TheCamera::Instance()->setTarget(m_pPlayer->getPosition());


	while (m_bRunning) {
		startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		waitTime = SDL_GetTicks() - startTime;
		if (waitTime < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - waitTime);
		}
	}
	clean();
}
Game::Game()
{
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	m_bRunning = true;
}
void Game::quit() {
	m_bRunning	= false;
}

Game::~Game()
{
}
