#pragma once
#include "stdafx.h"
#include "TankInputDeviceStateType.h"
#include "framework.h"


extern ALuint uiBuffer;
extern ALuint uiSource;

class UpdateTankPosCallback : public osg::NodeCallback
{
public:
	UpdateTankPosCallback(void);
	~UpdateTankPosCallback(void);
	UpdateTankPosCallback(TankInputDeviceStateType* tankIDevState, osg::Node* n);
	
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

protected:
	osg::Vec3f tankPos;
	osg::Vec3f tankVel;
	osg::ref_ptr<osg::Node> root;
	TankInputDeviceStateType* tankInputDeviceState;

	double angle;
};