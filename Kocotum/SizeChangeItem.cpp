#include "SizeChangeItem.hpp"

ShrinkItem::ShrinkItem(Vec2 pos, World& world)
	:Object{ pos, world, U"触れると小さくなるアイテム" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, isTouched{ false }
{ }


void ShrinkItem::restart()
{

}


bool ShrinkItem::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool ShrinkItem::mouseOver()
{
	return body.mouseOver();
}

void ShrinkItem::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void ShrinkItem::handleCollisionX()
{
	if (not isTouched)
	{
		world.player.setScale(0.75);
		//world.effect.add<ShrinkEffect>(body.center());
		isTouched = true;
	}
}

void ShrinkItem::handleCollisionY()
{
	if (not isTouched)
	{
		world.player.setScale(0.75);
		//world.effect.add<ShrinkEffect>(body.center());
		isTouched = true;
	}
}

void ShrinkItem::update()
{
	if (not intersectsPlayer())
	{
		isTouched = false;
	}
}

void ShrinkItem::draw() const
{
	TextureAsset(U"ShrinkItem").resized(CHIP_SIZE).draw(pos);
}



GrowItem::GrowItem(Vec2 pos, World& world)
	:Object{ pos, world, U"触れると大きくなるアイテム" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, isTouched{ false }
{ }


void GrowItem::restart()
{

}


bool GrowItem::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool GrowItem::mouseOver()
{
	return body.mouseOver();
}

void GrowItem::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void GrowItem::handleCollisionX()
{
	if (not isTouched)
	{
		world.player.setScale(2);
		//world.effect.add<GrowEffect>(body.center());
		isTouched = true;
	}
}

void GrowItem::handleCollisionY()
{
	if (not isTouched)
	{
		world.player.setScale(2);
		//world.effect.add<GrowEffect>(body.center());
		isTouched = true;
	}
}

void GrowItem::update()
{
	if (not intersectsPlayer())
	{
		isTouched = false;
	}
}

void GrowItem::draw() const
{
	TextureAsset(U"GrowItem").resized(CHIP_SIZE).draw(pos);
}
