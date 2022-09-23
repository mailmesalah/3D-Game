#pragma once

#include "stdafx.h"
#include "TankInputDeviceStateType.h"

class KeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
	KeyboardEventHandler(void);
	KeyboardEventHandler(TankInputDeviceStateType* tids) { tankInputDeviceState = tids; }
	~KeyboardEventHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&); 
	virtual void accept(osgGA::GUIEventHandlerVisitor& v) { v.visit(*this); }

protected:
	TankInputDeviceStateType* tankInputDeviceState;
};
