#include "TankInputDeviceStateType.h"

TankInputDeviceStateType::TankInputDeviceStateType(void)
{
	moveFwdRequest = false;
	moveBakRequest = false;
	moveLefRequest = false;
	moveRitRequest = false;
	j = false;
	k = false;
	q = false;
	e = false;
}

TankInputDeviceStateType::~TankInputDeviceStateType(void)
{
}
