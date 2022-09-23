#include <Windows.h>
#include <gl/GL.h>
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgDB/readFile>
#include <osg/Texture2D>
#include <osg/ShapeDrawable>
#include <osg/TexEnv>
#include <osgText/Text>
#include <osgDB/Registry>
#include <osgText/Font>
#include <osg/MatrixTransform>
#include <osg/Projection>
#include <osg/ShapeDrawable>
#include <osgGA/TrackballManipulator>
#include <osgUtil/IntersectVisitor>
#include <osgGA/KeySwitchMatrixManipulator>
#include <iostream>

using std::cout;
using std::endl;

#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgManipulatord.lib") 
#pragma comment(lib, "osgParticled.lib") 
#pragma comment(lib, "osgShadowd.lib") 
#pragma comment(lib, "osgSimd.lib")
#pragma comment(lib, "osgTerraind.lib") 
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
