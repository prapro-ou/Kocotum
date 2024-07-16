#include "SavePoint.hpp"

SavePoint::SavePoint(Vec2 pos, World& world)
	:Object{ pos, world, U"セーブポイント" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, isTouched{ false }
{ }


void SavePoint::restart()
{

}


bool SavePoint::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool SavePoint::mouseOver()
{
	return body.mouseOver();
}

void SavePoint::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void SavePoint::handleCollisionX()
{
	if (not isTouched)
	{
		world.savePlayer(pos);
		isTouched = true;
	}
}

void SavePoint::handleCollisionY()
{
	if (not isTouched)
	{
		world.savePlayer(pos);
		isTouched = true;
	}
}

void SavePoint::update()
{
	if (not intersectsPlayer())
	{
		isTouched = false;
	}
}

void SavePoint::draw() const
{
	body.draw(ColorF(0.5, 0.5, 0.25, 0.25));
}
