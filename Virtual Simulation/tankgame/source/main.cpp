#include <Windows.h>
#include <stdarg.h>
#include <osgWidget/Util>
#include <osgWidget/WindowManager>
#include <osgWidget/Box>
#include <osgWidget/Label>
#include <osgText/Text>

#include "KeyboardEventHandler.h"
#include "TankInputDeviceStateType.h"
#include "UpdateTankPosCallback.h"
#include "TransformAccumulator.h"
#include "FollowNodeMatrixManipulator.h"
#include "osgpick.h"

ALuint uiBuffer;
ALuint uiSource;


int main()
{
	printf("TANK DRIVING GAME \n");
	printf("------------------\n");
	printf("Instructions:\n");
	printf("Press W Key = Move Forward\n");
	printf("Press S Key = Move Backward\n");
	printf("Press A Key = Move Left\n");
	printf("Press D Key = Move Right\n");
	printf("Press J Key = Move Up\n");
	printf("Press K Key = Move Down\n");
	printf("Press Q Key = Turn Counter Clockwise\n");
	printf("Press E Key = Turn Clockwise\n");
	printf("Press 1 or 2 Key = Change View Point\n");
	printf("-------------------------------------\n");
	printf("Menu:\n");
	printf("Click on Speed Up = Increses Speed\n");
	printf("Click on Speed Down = Decreses Speed\n");
	printf("Click on Mute = Turns off Sound\n");

	//init OpenAL setting
	ALFWInit();
	if (!ALFWInitOpenAL())
	{
		printf("Failed to initialize OpenAL\n");
		ALFWShutdown();
		return 0;
	}
	// Generate an AL Buffer
	alGenBuffers( 1, &uiBuffer );
	// Load Wave file into OpenAL Buffer
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath("..\\audio\\engine.wav"), uiBuffer))
	{
		printf("Failed to load engine.wav\n");
	}

	// Generate a Source to playback the Buffer
    alGenSources( 1, &uiSource );
	// Attach Source to Buffer
	alSourcei( uiSource, AL_BUFFER, uiBuffer );

	//osg scene ground
	osg::Node* groundNode = NULL;
	groundNode = osgDB::readNodeFile("T72-tank/JoeDirt.flt");//("env.IVE");

	// tank
	osg::Node* tankNode = NULL; 
	tankNode = osgDB::readNodeFile("T72-tank/t72-tank_des.flt");

	// 
	//osg::Node* cowNode = NULL; 
	//cowNode = osgDB::readNodeFile("T72-tank/dumptruck.osg");
	//cowNode = osgDB::readNodeFile("data/aa.IVE");

	// Create green Irish sky
	osg::ClearNode* backdrop = new osg::ClearNode;
	backdrop->setClearColor(osg::Vec4(0.0f, 0.2f, 0.4f, 1.0f));
	
	osg::Group* root = new osg::Group();
	root->addChild(backdrop);
	root->addChild(groundNode);

	//osg::PositionAttitudeTransform* cowXform;
	//cowXform = new osg::PositionAttitudeTransform();
	//root->addChild(cowXform);
	//cowXform->addChild(cowNode);
	//cowXform->setPosition(osg::Vec3(-1, 10, 16));
	//cowXform->setScale(osg::Vec3(0.05, 0.05, 0.05));
	//cowXform->setScale(osg::Vec3(5, 5, 5));

	osg::PositionAttitudeTransform* tankXform;
	tankXform = new osg::PositionAttitudeTransform();
	root->addChild(tankXform);
	tankXform->addChild(tankNode);
	tankXform->setPosition(osg::Vec3(0, 0, 0));
	tankXform->setAttitude(
		osg::Quat(osg::DegreesToRadians(0.0), osg::Vec3(0, 0, 1)) );
	//tankXform->setScale(osg::Vec3(5, 5, 5));
	

	osg::PositionAttitudeTransform * followerOffset = 
		new osg::PositionAttitudeTransform(); 
	followerOffset->setPosition( osg::Vec3(0.0,-25.0,10) ); 
	followerOffset->setAttitude( 
			osg::Quat( osg::DegreesToRadians(-15.0), osg::Vec3(1,0,0) ) ); 
	tankXform->addChild(followerOffset);
	TransformAccumulator* tankFollowerWorldCoords = new TransformAccumulator(); 
	tankFollowerWorldCoords->attachToGroup(followerOffset);
	FollowNodeMatrixManipulator* followTank2 = new FollowNodeMatrixManipulator(tankFollowerWorldCoords);

	osg::Camera* hudCamera = new osg::Camera;
    hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    hudCamera->setProjectionMatrixAsOrtho2D(0,1280,0,1024);
    hudCamera->setViewMatrix(osg::Matrix::identity());
    hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
    hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

	osg::Vec3 position(150.0f,800.0f,0.0f);
    osg::Vec3 delta(0.0f,-60.0f,0.0f);
	const char *opts[]={"SpeedUp", "SpeedDown", "Mute"};
	for (int i=0; i<3; i++) {
        osg::Vec3 dy(0.0f,-30.0f,0.0f);
        osg::Vec3 dx(120.0f,0.0f,0.0f);
		osg::Vec3 dval(1.0f, 15.0f, 0.0f);
        osg::Geode* geode = new osg::Geode();
        osg::StateSet* stateset = geode->getOrCreateStateSet();
        
        osg::Geometry *quad=new osg::Geometry;
        stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
        stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
        std::string name = std::string(opts[i]);
        geode->setName(name);
        osg::Vec3Array* vertices = new osg::Vec3Array(4); // 1 quad
        osg::Vec4Array* colors = new osg::Vec4Array;
        colors = new osg::Vec4Array;
        colors->push_back(osg::Vec4(0.8-0.1*i,0.1*i,0.2*i, 0.1));
       // quad->setColorArray(colors, osg::Array::BIND_OVERALL);
        (*vertices)[0]=position;
        (*vertices)[1]=position+dx;
        (*vertices)[2]=position+dx+dy;
        (*vertices)[3]=position+dy;
        quad->setVertexArray(vertices);
        quad->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));
        geode->addDrawable(quad);
        hudCamera->addChild(geode);

		osgText::Text* text = new  osgText::Text;
        geode->addDrawable( text );
            //text->setFont(timesFont);
		text->setColor(osg::Vec4(0.8-0.1*i,0.1*i,0.2*i, 1.0));
        text->setPosition(position-dval);
		text->setCharacterSize(18);
        text->setText(opts[i]);

		
        position += delta;
    }
	
	root->addChild(hudCamera);
	/*osg::ref_ptr<osgText::Text> updateText = new osgText::Text;
	{ // this displays what has been selected
        osg::Geode* geode = new osg::Geode();
        osg::StateSet* stateset = geode->getOrCreateStateSet();
        stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
        stateset->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
        geode->setName("The text label");
        geode->addDrawable( updateText );
        hudCamera->addChild(geode);

        updateText->setCharacterSize(20.0f);
        //updateText->setFont(timesFont);
        updateText->setColor(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
        updateText->setText("");
        updateText->setPosition(position);
        updateText->setDataVariance(osg::Object::DYNAMIC);

        position += delta;
    }*/




    // add the HUD subgraph.
    
	osgViewer::Viewer viewer;
	viewer.realize();

	//osgGA::TrackballManipulator *Tman = new osgGA::TrackballManipulator();
	//viewer.setCameraManipulator(Tman);
	

	// capture keyborad event
	TankInputDeviceStateType* tIDevState = new TankInputDeviceStateType;
	// update status of tank, eg. speed/engine sound/position etc
	tankXform->setUpdateCallback(new UpdateTankPosCallback(tIDevState, root));
	
	// keyborad event handler
	KeyboardEventHandler* tankEventHandler = new KeyboardEventHandler(tIDevState);
	viewer.addEventHandler(tankEventHandler);	
	//viewer.addEventHandler(new PickHandler(updateText));
	viewer.setSceneData(root);					

	TransformAccumulator* tankWorldCoords = new TransformAccumulator();
	tankWorldCoords->attachToGroup(tankXform);
	FollowNodeMatrixManipulator* followTank = new FollowNodeMatrixManipulator(tankWorldCoords);
	
	osgGA::KeySwitchMatrixManipulator *ksmm = new osgGA::KeySwitchMatrixManipulator();
	if (!ksmm) return -1;

	// view manipular capture
	// 1 = seen from the back of the tank
	// 2 = seen at the front of the tank
	ksmm->addMatrixManipulator('1', "tankFollower2", followTank2);
	ksmm->addMatrixManipulator('2', "tankFollower", followTank);
	
	// the camera will follow the node movement
	viewer.setCameraManipulator(ksmm);

	while (!viewer.done())
	{
		viewer.frame();
	}
}