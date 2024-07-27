#include "TrojanDestroy.hpp"

TrojanDestroy::TrojanDestroy(Vec2 pos, World& world)
	: Object{ pos, world, U"トロイフォース：破壊" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, isGet{ false }
{
}

void TrojanDestroy::restart()
{
	isGet = false;
}

bool TrojanDestroy::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool TrojanDestroy::mouseOver()
{
	return body.mouseOver();
}

void TrojanDestroy::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void TrojanDestroy::handleCollisionX()
{
	if (not isGet)
	{
		world.trojanEnable[(size_t)Trojan::Destroy] = true;
		isGet = true;
	}
}

void TrojanDestroy::handleCollisionY()
{
	if (not isGet)
	{
		world.trojanEnable[(size_t)Trojan::Destroy] = true;
		isGet = true;
	}
}

void TrojanDestroy::update()
{
}

void TrojanDestroy::draw() const
{
	if (not isGet)
	{
		TextureAsset(U"TrojanDestroy").resized(CHIP_SIZE).draw(pos);
	}
}
