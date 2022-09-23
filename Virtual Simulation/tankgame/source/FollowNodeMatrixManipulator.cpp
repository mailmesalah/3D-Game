#include "FollowNodeMatrixManipulator.h"

FollowNodeMatrixManipulator::FollowNodeMatrixManipulator(void)
{ 
}

FollowNodeMatrixManipulator::~FollowNodeMatrixManipulator(void)
{
}

FollowNodeMatrixManipulator::FollowNodeMatrixManipulator( TransformAccumulator* ta)
{
	worldCoordinatesOfNode = ta; 
	theMatrix = osg::Matrixd::identity();
}
void FollowNodeMatrixManipulator::updateTheMatrix()
{
    theMatrix = worldCoordinatesOfNode->getMatrix();
}
osg::Matrixd FollowNodeMatrixManipulator::getMatrix() const
{
    return theMatrix;
}
osg::Matrixd FollowNodeMatrixManipulator::getInverseMatrix() const
{
	// 将矩阵从Y轴向上旋转到Z轴向上
	osg::Matrixd m;
	m = theMatrix * osg::Matrixd::rotate(-3.14/2.0, osg::Vec3(1,0,0) );
	return m;
}
void FollowNodeMatrixManipulator::setByMatrix(const osg::Matrixd& mat)
{
    theMatrix = mat;
}
void FollowNodeMatrixManipulator::setByInverseMatrix(const osg::Matrixd& mat)
{
    theMatrix = mat.inverse(mat);
}

bool FollowNodeMatrixManipulator::handle(const osgGA::GUIEventAdapter&ea, 
										 osgGA::GUIActionAdapter&aa)
{
	switch(ea.getEventType())
	{
	case (osgGA::GUIEventAdapter::FRAME):
		{
		updateTheMatrix();
		return false;
		}
	}
	return false;
}