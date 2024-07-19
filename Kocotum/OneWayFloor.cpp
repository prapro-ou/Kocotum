#include "OneWayFloor.hpp"

OneWayFloor::OneWayFloor(Vec2 pos, World& world)
	: Object{ pos, world, U"下から通れる足場" }
	, body{ RectF{ pos, CHIP_SIZE.x, CHIP_SIZE.y / 2 } }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
{
}

void OneWayFloor::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool OneWayFloor::intersectsPlayer()
{
	return body.intersects(world.player.body.bottom());
}

bool OneWayFloor::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void OneWayFloor::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
	mouseOverBody.setPos(pos);
}

void OneWayFloor::handleCollisionX()
{
	// x軸方向は衝突判定をしない
}

void OneWayFloor::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (world.player.isGravityReverse)
	{
		// 重力反転時の処理
		if (world.player.velocity.y > 0)
		{
			world.player.pos.y = pos.y + CHIP_SIZE.y / 4;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;

			world.player.friction = 1.0;
			world.player.velocity.y = 0.01;
		}
	}
	else
	{
		// 通常重力時の処理
		if (world.player.velocity.y > 0)
		{
			world.player.pos.y = pos.y - world.player.body.h;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;

			world.player.friction = 1.0;
			world.player.velocity.y = 0.01;
		}
	}

	world.player.body.setPos(world.player.pos);
}

void OneWayFloor::update()
{
	// 更新処理（現在は何もしない）
}

void OneWayFloor::draw() const
{
	// 壁のテクスチャを描画
	TextureAsset(U"OneWayFloor").resized(CHIP_SIZE).draw(pos);
}
