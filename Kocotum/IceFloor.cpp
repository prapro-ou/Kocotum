#include "IceFloor.hpp"

IceFloor::IceFloor(Vec2 pos, World& world)
	: Object{ pos, world, U"滑る床" }
	, body{ RectF{pos, CHIP_SIZE} }
{

}

/// @brief オブジェクトのリスタート
void IceFloor::restart()
{
	// 再起動時の処理（現在は何もしない）
}

/// @brief プレイヤーとの衝突判定
/// @return プレイヤーと衝突していればtrue、そうでなければfalse
bool IceFloor::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

/// @brief マウスオーバー判定
/// @return マウスがオブジェクト上にあればtrue、そうでなければfalse
bool IceFloor::mouseOver()
{
	return body.mouseOver();
}

/// @brief 位置の設定
/// @param newPos 新しい位置
void IceFloor::setPos(Vec2 pos)
{
	body.setPos(pos);
	this->pos = pos;
}

void IceFloor::handleCollisionX()
{
	// プレイヤーとの水平方向の衝突処理
	// 右方向に進行中の場合
	if (world.player.velocity.x > 0)
	{
		world.player.pos.x = pos.x - world.player.body.w;
	}
	// 左方向に進行中の場合
	else
	{
		world.player.pos.x = pos.x + CHIP_SIZE.x;
	}

	world.player.velocity.x = 0;
	world.player.body.setPos(world.player.pos);
}

	// プレイヤーとの垂直方向の衝突処理
void IceFloor::handleCollisionY()
{
	// 重力反転時の処理
	if (world.player.isGravityReverse)
	{
		if (world.player.velocity.y > 0)
		{
			world.player.pos.y = pos.y + CHIP_SIZE.y;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;
		}
		else
		{
			world.player.pos.y = pos.y - world.player.body.h;
		}
	}
	// 通常重力時の処理
	else
	{
		if (world.player.velocity.y > 0)
		{
			world.player.pos.y = pos.y - world.player.body.h;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;
		}
		else
		{
			world.player.pos.y = pos.y + CHIP_SIZE.y;
		}
	}

	world.player.velocity.y = 0.01;
	world.player.body.setPos(world.player.pos);
}

void IceFloor::update()
{
	// 更新処理（現在は何もしない）
}

void IceFloor::draw() const
{
	// 滑る床のテクスチャを描画
	TextureAsset(U"IceFloor").resized(CHIP_SIZE).draw(pos);
}
