#include "TransformAccumulator.h"

TransformAccumulator::TransformAccumulator(void)
{
	parent = NULL;
	node = new osg::Node;
	mpcb = new UpdateAccumulatedMatrix();
	node->setUpdateCallback(mpcb);
}

TransformAccumulator::~TransformAccumulator(void)
{
}

osg::Matrix TransformAccumulator::getMatrix()
{
	return mpcb->matrix;
}

//callback function of the TransformAccumulator
bool TransformAccumulator::attachToGroup(osg::Group* g)
{
	bool success = false;
	if (parent != NULL)
	{
		int n = parent->getNumChildren();
		for (int i = 0; i < n; i++)
		{
			if (node == parent->getChild(i) )
			{
				parent->removeChild(i,1);
				success = true;
			}
		}
		if (! success)
		{
			return success;
		}
	}
	g->addChild(node);
	return true;
}