#pragma once

class TankInputDeviceStateType
{
public:
	TankInputDeviceStateType(void);
	~TankInputDeviceStateType(void);

	bool moveFwdRequest;
	bool moveBakRequest;
	bool moveLefRequest;
	bool moveRitRequest;

	bool j;
	bool k;
	bool q;
	bool e;
};
