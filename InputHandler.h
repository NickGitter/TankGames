#pragma once
#include "SDL.h"
#include <vector>
#include <iostream>
#include "Vector2D.h"
const int m_joystickDeadZone = 10000;
enum mouse_buttons
{
	LEFT	= 0,
	MIDDLE	= 1,
	RIGHT	= 2
};
class InputHandler
{
public:
	static InputHandler* Instance() {
		if (s_pInstance == nullptr)
			s_pInstance = new InputHandler;
		return	s_pInstance;
	}
	void	reset()									{	for (int i = 0; i < m_mouseButtonStates.size(); ++i)m_mouseButtonStates[i] = false;}
	void	initialiseJoysticks();
	void	update();
	void	clean();
	int		xvalue(int joy, int stick);
	int		yvalue(int joy, int stick);
	bool joysticksInitialised()						{	return m_bJoysticksInitialised;				}
	bool getButtonState(int joy, int buttonNumber)	{	return m_buttonStates[joy][buttonNumber];	}
	bool getMouseButtonState(int buttonNumber)		{	return m_mouseButtonStates[buttonNumber];	}
	Vector2D* getMousePosition()					{	return m_mousePosition;						}
	bool isKeyDown(SDL_Scancode key);
	~InputHandler();
private:
	Vector2D* m_mousePosition;
	std::vector<bool>								m_mouseButtonStates	;
	std::vector<std::vector<bool>>					m_buttonStates		;
	std::vector<SDL_Joystick*>						m_joysticks			;
	std::vector<std::pair<Vector2D*, Vector2D*>>	m_joystickValues	; 
	Uint8*											m_keystates			;
	bool m_bJoysticksInitialised;
private:
	InputHandler();
	static InputHandler* s_pInstance;

private:
	// private functions to handle different event types
	// handle keyboard events
	void onKeyDown();
	void onKeyUp();
	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	// handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);
};

typedef InputHandler TheInputHandler;