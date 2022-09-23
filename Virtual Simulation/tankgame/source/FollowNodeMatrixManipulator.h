#pragma once
#include "stdafx.h"
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>
#include "TransformAccumulator.h"

class FollowNodeMatrixManipulator : public osgGA::NodeTrackerManipulator
{
public:
	FollowNodeMatrixManipulator(void);
	~FollowNodeMatrixManipulator(void);

	FollowNodeMatrixManipulator(TransformAccumulator* ta); 
	bool handle (const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa);
	void updateTheMatrix();
	virtual void setByMatrix(const osg::Matrixd& mat);
	virtual void setByInverseMatrix(const osg::Matrixd&mat);
	virtual osg::Matrixd getInverseMatrix() const;
	virtual osg::Matrixd getMatrix() const;
	
protected:
	TransformAccumulator* worldCoordinatesOfNode;
	osg::Matrixd theMatrix;
};
