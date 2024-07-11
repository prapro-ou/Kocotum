#include "StartPoint.hpp"

StartPoint::StartPoint(Vec2 pos, World& world)
	:Object{ pos, world, E_ObjectType::StartPoint, U"スタート位置" }
	, body{ RectF{ pos, CHIP_SIZE } }
{ }


void StartPoint::restart()
{

}


bool StartPoint::intersectsPlayer()
{
	//return false;
	return body.intersects(world.player.body);
}

bool StartPoint::mouseOver()
{
	return body.mouseOver();
}

void StartPoint::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void StartPoint::handleCollisionX()
{

}

void StartPoint::handleCollisionY()
{

}

void StartPoint::update()
{

}

void StartPoint::draw() const
{
	TextureAsset(U"StartPoint").resized(CHIP_SIZE).draw(pos);
}
