#include "WarpPoint.hpp"

WarpPoint::WarpPoint(Vec2 pos, World& world, String fileName)
	:Object{ pos, world, E_ObjectType::WarpPoint, U"ワープポイント" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, fileName{ fileName }
	, isTouched{ false }
{ }


void WarpPoint::restart()
{

}


bool WarpPoint::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool WarpPoint::mouseOver()
{
	return body.mouseOver();
}

void WarpPoint::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void WarpPoint::handleCollisionX()
{
	if (not isTouched)
	{
		world.loadWorld(fileName);
		System::Sleep(100ms);
		world.init();

		isTouched = true;
	}
}

void WarpPoint::handleCollisionY()
{
	if (not isTouched)
	{
		world.loadWorld(fileName);
		System::Sleep(100ms);
		world.init();

		isTouched = true;
	}
}

void WarpPoint::update()
{
	if (not intersectsPlayer())
	{
		isTouched = false;
	}
}

void WarpPoint::draw() const
{
	body.draw(ColorF(0.25, 0.5, 0.5, 0.25));
}
