#include "KeyboardEventHandler.h"
#include <iostream>

KeyboardEventHandler::KeyboardEventHandler(void)
{
}

KeyboardEventHandler::~KeyboardEventHandler(void)
{
}

//event handler for tank control button
// 'w' forward
//  's' backward
// 'a' left
// 'd' right
// 'j' up
// 'k' down
// 'q' turn around at counter-clockwise
// 'e' turn around at clockwise
bool KeyboardEventHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa) 
{ 
	switch(ea.getEventType())
	{ 
	case osgGA::GUIEventAdapter::KEYDOWN:
		{
			switch(ea.getKey()) 
			{
			case 'w': 
				std::cout << " w key down" << std::endl;
				tankInputDeviceState->moveFwdRequest = true;
				return false; 
				break;
			case 's':
				std::cout << " s key down" << std::endl;
				tankInputDeviceState->moveBakRequest = true;
				return false;
				break;
			case 'a':
				std::cout << " a key down" << std::endl;
				tankInputDeviceState->moveLefRequest = true;
				return false;
				break;
			case 'd':
				std::cout << " d key down" << std::endl;
				tankInputDeviceState->moveRitRequest = true;
				return false;
				break;

			case 'j':
				tankInputDeviceState->j = true;
				return false;
				break;
			case 'k':
				tankInputDeviceState->k = true;
				return false;
				break;
			case 'q':
				tankInputDeviceState->q = true;
				return false;
				break;
			case 'e':
				tankInputDeviceState->e = true;
				return false;
				break;
			default:
				return false;
			}
		}
	case osgGA::GUIEventAdapter::KEYUP:
		{
			switch(ea.getKey()) 
			{
			case 'w':
				std::cout << " w key up" << std::endl;
				tankInputDeviceState->moveFwdRequest = false;
				return false; 
				break;
			case 's':
				std::cout << " s key up" << std::endl;
				tankInputDeviceState->moveBakRequest = false;
				return false;
				break;
			case 'a':
				std::cout << " a key up" << std::endl;
				tankInputDeviceState->moveLefRequest = false;
				return false;
				break;
			case 'd':
				std::cout << " d key up" << std::endl;
				tankInputDeviceState->moveRitRequest = false;
				return false;
				break;

			case 'j':
				tankInputDeviceState->j = false;
				return false;
				break;
			case 'k':
				tankInputDeviceState->k = false;
				return false;
				break;
			case 'q':
				tankInputDeviceState->q = false;
				return false;
				break;
			case 'e':
				tankInputDeviceState->e = false;
				return false;
				break;
			default:
				return false;
			}
		}
	default:
		return false;
	}
}
