
#include "UpdateTankPosCallback.h"
#include "osgpick.h"

UpdateTankPosCallback::UpdateTankPosCallback(void)
{
	angle = 0.0;
}

UpdateTankPosCallback::~UpdateTankPosCallback(void)
{
}

// constructor of UpdateTankPosCallback
UpdateTankPosCallback::UpdateTankPosCallback(TankInputDeviceStateType* tankIDevState, osg::Node* n) 
	: tankPos(0.0, 0.0, 10.0), tankVel(0.0, 0.0, 0.0)
{
	tankInputDeviceState = tankIDevState;
	root = n;
	angle = 0.0;
}

// update the tank position by caculat its speed/position
// engine sound is added here to0.
void UpdateTankPosCallback::operator()(osg::Node* node, osg::NodeVisitor* nv) 
{
	static bool bplay = false;
	osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*> (node); 
	if (pat)
	{
		//movement speed
		float const_move_vel = 0.05 + g_speed*0.01;
		
		//calculate direction of left/right/forward/backward
		if (tankInputDeviceState->moveFwdRequest)
		{
			tankVel.x() = -const_move_vel * sin(angle);
			tankVel.y() =  const_move_vel * cos(angle);
			//cout<<sin(angle)<<" "<<tankVel.x()<<" "<<cos(angle)<<" "<<tankVel.y()<<endl;
			if( !bplay && !g_bmute)
			{
				alSourcePlay( uiSource );
				bplay = true;
			}
		}
		else if (tankInputDeviceState->moveBakRequest)
		{
			tankVel.x() =  const_move_vel * sin(angle);
			tankVel.y() = -const_move_vel * cos(angle);
			if( !bplay && !g_bmute)
			{
				alSourcePlay( uiSource );
				bplay = true;
			}
		}
		else if (tankInputDeviceState->moveLefRequest)
		{
			/*
			tankVel.x() = -const_move_vel * cos(angle);
			tankVel.y() = -const_move_vel * sin(angle);
			*/
			angle += 0.002;
			tankVel.x() = -const_move_vel * sin(angle);
			tankVel.y() =  const_move_vel * cos(angle);
			if( !bplay && !g_bmute)
			{
				alSourcePlay( uiSource );
				bplay = true;
			}
		}
		else if (tankInputDeviceState->moveRitRequest)
		{
			/*
			tankVel.x() =  const_move_vel * cos(angle);
			tankVel.y() =  const_move_vel * sin(angle);
			*/
			angle -= 0.002;
			tankVel.x() = -const_move_vel * sin(angle);
			tankVel.y() =  const_move_vel * cos(angle);
			if( !bplay && !g_bmute )
			{
				alSourcePlay( uiSource );
				bplay = true;
			}
		}
		//if don't push direction button, then speed is 0, no more movement
		else if ((!tankInputDeviceState->moveLefRequest) && (!tankInputDeviceState->moveRitRequest)
			&& (!tankInputDeviceState->moveFwdRequest) && (!tankInputDeviceState->moveBakRequest))
		{
			tankVel = osg::Vec3f(0.0, 0.0, 0.0);
			if( bplay )
			{
				alSourceStop( uiSource);
				bplay = false;
			}
		}

		//press j, will give a upward movement speed
		if (tankInputDeviceState->j)
			tankVel.z() = const_move_vel;
		//press k, will give a downward movement speed
		else if (tankInputDeviceState->k)
			tankVel.z() = -const_move_vel;
		//if j and k are not pressed, speed of axis z is 0
		else if ((!tankInputDeviceState->j) && (!tankInputDeviceState->k)){
			tankVel.z() = 0;
		}
		//q clockwise movement
		//e counter-clockwise movement
		if (tankInputDeviceState->q)
			angle += 0.01;
		else if (tankInputDeviceState->e)
			angle -= 0.01;
		//tankVel.z() += 0.5;
		//std::cout << angle << endl;
		
		pat->setAttitude(osg::Quat(angle, osg::Z_AXIS));

		osg::Vec3 newPos = tankPos + tankVel * 6;
		osgUtil::IntersectVisitor iv;
		node->setNodeMask(0x0);

		osg::ref_ptr<osg::LineSegment> line_low = new osg::LineSegment(newPos, tankPos);
		iv.addLineSegment(line_low.get());

		root->accept(iv);
		node->setNodeMask(0xffffffff);
		//calculate the collision
		if (iv.hits())					//hit hte low end area
		{
			osg::Vec3f ip_low;
			osg::Vec3f ip_hight;
			float low_distant;
			float hight_distant;
			

			osgUtil::IntersectVisitor::HitList& hitList = iv.getHitList(line_low.get());
			if (!hitList.empty())
			{
				//get the hit point
				ip_low = hitList.front().getWorldIntersectPoint();
				low_distant = (ip_low.x() - tankPos.x())*(ip_low.x() - tankPos.x())
						+ (ip_low.y() - tankPos.y())*(ip_low.y() - tankPos.y());
			}

			iv.reset();
			node->setNodeMask(0x0);
			const float hight = 1.732;
			osg::Vec3f hight_new_pos = tankPos + tankVel * 10;

			osg::ref_ptr<osg::LineSegment> line_hight = new osg::LineSegment(
				newPos + osg::Vec3(0.0, 0.0, hight), hight_new_pos + osg::Vec3(0.0, 0.0, hight));
			
			iv.addLineSegment(line_hight);
			root->accept(iv);
			node->setNodeMask(0xffffffff);
			if (iv.hits())				// hit the high end area
			{
				osgUtil::IntersectVisitor::HitList& hitList = iv.getHitList(line_hight.get());
				if (!hitList.empty())
				{
					//get hit point
					ip_hight = hitList.front().getWorldIntersectPoint();
					hight_distant = (ip_hight.x() - tankPos.x())*(ip_hight.x() - tankPos.x())
						+ (ip_hight.y() - tankPos.y())*(ip_hight.y() - tankPos.y());

					if (sqrt(hight_distant) - sqrt(low_distant) < 1) // to slope to clime
					{
						pat->setPosition(tankPos);
						traverse(node, nv);
						return;
					}
				}
			}
		}

		// detect the height of the scene
		iv.reset();
		node->setNodeMask(0x0);

		osg::ref_ptr<osg::LineSegment> lineZ = new osg::LineSegment(
			newPos - osg::Vec3f(0.0, 0.0, 5.0), newPos + osg::Vec3f(0.0, 0.0, 5.0));
		iv.addLineSegment(lineZ.get());

		root->accept(iv);
		node->setNodeMask(0xffffffff);
		if (iv.hits())
		{
			osgUtil::IntersectVisitor::HitList& hitList = iv.getHitList(lineZ.get());
			if (!hitList.empty())
            {
                //get collision point
                osg::Vec3d ip = hitList.front().getWorldIntersectPoint();
				tankPos.z() = ip.z();
				
				// 
				//tankPos.z() = ip.z() + 1.0;
            }
		}

		tankPos += tankVel;
		pat->setPosition(tankPos);
	}
	traverse(node, nv);
}