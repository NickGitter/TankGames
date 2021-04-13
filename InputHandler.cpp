#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;
void InputHandler::update()		{
	SDL_Event event;
	int whichOne;
	m_keystates =  (Uint8*)SDL_GetKeyboardState(0);
	//ожидаем получения события
	while (SDL_PollEvent(&event)) 
	{
		//какое именно событие
		switch (event.type) 
		{
		case SDL_QUIT:	//выход из игры
			TheGame::Instance()->quit();
			break;
		case SDL_JOYAXISMOTION:
			onJoystickAxisMove	(event);
			break;
		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;
		case SDL_JOYBUTTONUP:
			onJoystickButtonUp	(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_MOUSEWHEEL:
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_KEYDOWN:
			std::cout << "SDL_KEY_DOWN_EVENT";
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		}
	}
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
int InputHandler::xvalue(int joy, int stick) {
	if (m_joystickValues.size() > 0){
		if (stick == 1)
			return m_joystickValues[joy].first->getX();
		else 
			if (stick == 2)
				return m_joystickValues[joy].second->getX();
	}
	return 0;
}
int InputHandler::yvalue(int joy, int stick) {
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->getY();
		}
	}
	return 0;
}
void InputHandler::clean()		{
	if (m_bJoysticksInitialised)
	for (int i = 0; i < m_joysticks.size(); ++i)
		SDL_JoystickClose(m_joysticks[i]);
	
}
void InputHandler::initialiseJoysticks() {
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	if (SDL_NumJoysticks() > 0) {
		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			SDL_Joystick* joy = nullptr;
			joy=SDL_JoystickOpen(i);
			if (joy != nullptr){
				m_joysticks.push_back(joy); 
				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
					tempButtons.push_back(false);
				m_buttonStates.push_back(tempButtons);
			}
			else {
				std::cout << SDL_GetError() << "\n";
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Инициализированно " << m_joysticks.size() << " геймпадов\n";
	}
	else{
		std::cout << "Инициализированно " << m_joysticks.size() << " геймпадов\n";
		m_bJoysticksInitialised = false;
	}
}
//private:
void InputHandler::onKeyDown() {
}
void InputHandler::onKeyUp() {
}
// handle mouse events
void InputHandler::onMouseMove			(SDL_Event& event) {
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}
void InputHandler::onMouseButtonDown	(SDL_Event& event) {
	switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			m_mouseButtonStates[LEFT	] = true;
			break;
		case SDL_BUTTON_MIDDLE:
			m_mouseButtonStates[MIDDLE	] = true;
			break;
		case SDL_BUTTON_RIGHT:
			m_mouseButtonStates[RIGHT	] = true;
			break;
		default:
			break;
	}
}
void InputHandler::onMouseButtonUp		(SDL_Event& event) {
	switch (event.button.button) {
	case SDL_BUTTON_LEFT:
		m_mouseButtonStates[LEFT] = false;
		break;
	case SDL_BUTTON_MIDDLE:
		m_mouseButtonStates[MIDDLE] = false;
		break;
	case SDL_BUTTON_RIGHT:
		m_mouseButtonStates[RIGHT] = false;
		break;
	}
}
// handle joysticks events
void InputHandler::onJoystickAxisMove	(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	switch (event.jaxis.axis) {
	case 0:
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setX(0);
		}
		break;
	case 1:
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].first->setY(0);
		}
		break;
	case 3:
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setX(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setX(0);
		}
		break;
	case 4:
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->setY(-1);
		}
		else
		{
			m_joystickValues[whichOne].second->setY(0);
		}
		break;
	}
}
void InputHandler::onJoystickButtonDown	(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = true;
}
void InputHandler::onJoystickButtonUp	(SDL_Event& event) {
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}
//Конструктор деструктор
InputHandler::InputHandler()	{
	for (int i = 0; i < 3; i++)
		m_mouseButtonStates.push_back(false);
	m_mousePosition = new Vector2D();
	m_keystates = new Uint8[256];
}
InputHandler::~InputHandler()	{
}