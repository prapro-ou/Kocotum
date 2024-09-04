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
