# include "JumpItem.hpp"

JumpItem::JumpItem(Vec2 pos, World& world)
	: Object{ pos, world, U"ジャンプ回数復活アイテム", textureIndex }
	, isGot{ false }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ Polygon{ CHIP_SIZE / 2.0 + Vec2{ 0.0, -CHIP_SIZE.y / 4.0 },
					CHIP_SIZE / 2.0 + Vec2{ CHIP_SIZE.x / 4.0, 0.0 },
					CHIP_SIZE / 2.0 + Vec2{ 0.0, CHIP_SIZE.y / 4.0 },
					CHIP_SIZE / 2.0 + Vec2{ -CHIP_SIZE.x / 4.0, 0.0 }} }
{
	body.moveBy(pos);
	sw.reset();
}

void JumpItem::restart()
{
	isGot = false;
	sw.reset();
}

bool JumpItem::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool JumpItem::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void JumpItem::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	body.moveBy(pos - this->pos);
	this->pos = pos;
}

void JumpItem::handleCollisionX()
{
	if (not isGot)
	{
		world.player.jumpNum--;
		isGot = true;
		sw.restart();
	}
}

void JumpItem::handleCollisionY()
{
	if (not isGot)
	{
		world.player.jumpNum--;
		isGot = true;
		sw.restart();
	}
}

void JumpItem::update()
{
	if (isGot)
	{
		if (sw.sF() > 5)
		{
			isGot = false;
		}
	}
}

void JumpItem::draw() const
{
	if (isGot)
	{
		Circle{ pos.x + 25, pos.y + 25, 3 }.draw();
	}
	else
	{
		body.draw(Palette::Aqua);
	}
}
