#pragma once
#include "stdafx.h"
#include "updateAccumulatedMatrix.h"

class TransformAccumulator
{
public:
	TransformAccumulator(void);
	~TransformAccumulator(void);

	bool attachToGroup(osg::Group* g);
	osg::Matrix getMatrix();

protected:
	osg::ref_ptr<osg::Group> parent;
	osg::Node* node;
	UpdateAccumulatedMatrix* mpcb;
};
