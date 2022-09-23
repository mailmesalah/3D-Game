#pragma once
#include "stdafx.h"

class UpdateAccumulatedMatrix : public osg::NodeCallback
{
public:
	UpdateAccumulatedMatrix(void);
	~UpdateAccumulatedMatrix(void);

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		matrix = osg::computeWorldToLocal(nv->getNodePath());
		traverse(node, nv);
	}
	
	osg::Matrix matrix;
};
