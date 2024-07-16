#include "GravityLine.hpp"

GravityLineHorizontal::GravityLineHorizontal(Vec2 pos, World& world, double length)
	: Object{ pos, world, U"重力線:横" }
	, length{ length }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ RectF{ pos + Vec2{ 0, CHIP_SIZE.y / 2 }, length, 5 } }
	, isTouched{ false }
{ }

void GravityLineHorizontal::restart()
{
	isTouched = false;
}

bool GravityLineHorizontal::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool GravityLineHorizontal::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void GravityLineHorizontal::setPos(Vec2 pos)
{
	this->pos = pos;
	mouseOverBody.setPos(pos);
	body.setPos(pos + Vec2{ 0, CHIP_SIZE.y / 2.0 });
}

void GravityLineHorizontal::handleCollisionX()
{
	if (!isTouched)
	{
		// プレイヤーの重力を反転させる
		world.player.velocity.y = 5;
		world.player.gravityDirection *= -1;
		world.player.isGravityReverse = !world.player.isGravityReverse;
		isTouched = true;
	}
}

void GravityLineHorizontal::handleCollisionY()
{
	if (!isTouched)
	{
		// プレイヤーの重力を反転させる
		world.player.velocity.y = 5;
		world.player.gravityDirection *= -1;
		world.player.isGravityReverse = !world.player.isGravityReverse;
		isTouched = true;
	}
}

void GravityLineHorizontal::update()
{
	body.setSize(length, 5);
	mouseOverBody.setSize(length, CHIP_SIZE.y);

	if (!intersectsPlayer())
	{
		isTouched = false;
	}
}

void GravityLineHorizontal::draw() const
{
	double alpha = (isTouched ? 0.5 : 1);
	body.draw(ColorF(1, alpha));
}

GravityLineVertical::GravityLineVertical(Vec2 pos, World& world, double length)
	: Object{ pos, world, U"重力線:縦" }
	, length{ length }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ RectF{ pos + Vec2{ CHIP_SIZE.x / 2, 0 }, 5, length } }
	, isTouched{ false }
{ }

void GravityLineVertical::restart()
{
	isTouched = false;
}

bool GravityLineVertical::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool GravityLineVertical::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void GravityLineVertical::setPos(Vec2 pos)
{
	this->pos = pos;
	mouseOverBody.setPos(pos);
	body.setPos(pos + Vec2{ CHIP_SIZE.x / 2.0, 0 });
}

void GravityLineVertical::handleCollisionX()
{
	if (!isTouched)
	{
		// プレイヤーの重力を反転させる
		world.player.velocity.y = 5;
		world.player.gravityDirection *= -1;
		world.player.isGravityReverse = !world.player.isGravityReverse;
		isTouched = true;
	}
}

void GravityLineVertical::handleCollisionY()
{
	if (!isTouched)
	{
		// プレイヤーの重力を反転させる
		world.player.velocity.y = 5;
		world.player.gravityDirection *= -1;
		world.player.isGravityReverse = !world.player.isGravityReverse;
		isTouched = true;
	}
}

void GravityLineVertical::update()
{
	body.setSize(5, length);
	mouseOverBody.setSize(CHIP_SIZE.x, length);

	if (!intersectsPlayer())
	{
		isTouched = false;
	}
}

void GravityLineVertical::draw() const
{
	double alpha = (isTouched ? 0.5 : 1);
	body.draw(ColorF(1, alpha));
}
