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
	TextureAsset(U"SavePoint").resized(CHIP_SIZE).draw(pos + Vec2{ 0, Periodic::Sine1_1(2s) * CHIP_SIZE.y / 16 }, (isTouched ? Palette::Mediumspringgreen : Palette::Lightskyblue));
}
