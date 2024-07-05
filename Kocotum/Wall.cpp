#include "Wall.hpp"

Wall::Wall(Vec2 pos, Effect& effect, Player& player)
	: Object{ pos, effect, player, E_ObjectType::Wall, U"壁" }
	, body{ RectF{ pos, CHIP_SIZE } }
{
}

void Wall::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool Wall::intersectsPlayer()
{
	return body.intersects(player.body);
}

bool Wall::mouseOver()
{
	return body.mouseOver();
}

void Wall::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void Wall::handleCollisionX()
{
	// プレイヤーとの水平方向の衝突処理
	if (player.velocity.x > 0)
	{
		// 右方向に進行中の場合
		player.pos.x = pos.x - player.body.w;
	}
	else
	{
		// 左方向に進行中の場合
		player.pos.x = pos.x + CHIP_SIZE.x;
	}

	player.velocity.x = 0;
	player.body.setPos(player.pos);
}

void Wall::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (player.isGravityReverse)
	{
		// 重力反転時の処理
		if (player.velocity.y > 0)
		{
			player.pos.y = pos.y + CHIP_SIZE.y;
			player.jumpNum = 0;
			player.isOnGround = true;
		}
		else
		{
			player.pos.y = pos.y - player.body.h;
		}
	}
	else
	{
		// 通常重力時の処理
		if (player.velocity.y > 0)
		{
			player.pos.y = pos.y - player.body.h;
			player.jumpNum = 0;
			player.isOnGround = true;
		}
		else
		{
			player.pos.y = pos.y + CHIP_SIZE.y;
		}
	}

	player.velocity.y = 0.01;
	player.body.setPos(player.pos);
}

void Wall::update()
{
	// 更新処理（現在は何もしない）
}

void Wall::draw() const
{
	// 壁のテクスチャを描画
	TextureAsset(U"Wall").resized(CHIP_SIZE).draw(pos);
}

JumpToggleWall::JumpToggleWall(Vec2 pos, Effect& effect, Player& player, bool init)
	: Object{ pos, effect, player, E_ObjectType::JumpToggleWall, U"ジャンプで切り替わる壁" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, init{ init }
	, isOn{ init }
{
}

void JumpToggleWall::restart()
{
	// 再起動時に初期状態に戻す
	isOn = init;
}

bool JumpToggleWall::intersectsPlayer()
{
	return body.intersects(player.body);
}

bool JumpToggleWall::mouseOver()
{
	return body.mouseOver();
}

void JumpToggleWall::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void JumpToggleWall::setInit(bool init)
{
	this->init = init;
	this->isOn = init;
}

void JumpToggleWall::handleCollisionX()
{
	// 壁がオンの場合のみ衝突処理を行う
	if (isOn)
	{
		// プレイヤーとの水平方向の衝突処理
		if (player.velocity.x > 0)
		{
			// 右方向に進行中の場合
			player.pos.x = pos.x - player.body.w;
		}
		else
		{
			// 左方向に進行中の場合
			player.pos.x = pos.x + CHIP_SIZE.x;
		}

		player.velocity.x = 0;
	}

	player.body.setPos(player.pos);
}

void JumpToggleWall::handleCollisionY()
{
	// 壁がオンの場合のみ衝突処理を行う
	if (isOn)
	{
		// プレイヤーとの垂直方向の衝突処理
		if (player.isGravityReverse)
		{
			// 重力反転時の処理
			if (player.velocity.y > 0)
			{
				player.pos.y = pos.y + CHIP_SIZE.y;
				player.jumpNum = 0;
				player.isOnGround = true;
			}
			else
			{
				player.pos.y = pos.y - player.body.h;
			}
		}
		else
		{
			// 通常重力時の処理
			if (player.velocity.y > 0)
			{
				player.pos.y = pos.y - player.body.h;
				player.jumpNum = 0;
				player.isOnGround = true;
			}
			else
			{
				player.pos.y = pos.y + CHIP_SIZE.y;
			}
		}

		player.velocity.y = 0.01;
	}

	player.body.setPos(player.pos);
}

void JumpToggleWall::update()
{
	// プレイヤーがジャンプした時に壁の状態を切り替える
	if (player.jumpNum < player.maxJumpNum && KeySpace.down() && player.isAlive)
	{
		isOn = !isOn; // 状態を反転
	}
}

void JumpToggleWall::draw() const
{
	// 壁の状態に応じたテクスチャを描画
	TextureAsset((isOn ? U"JumpToggleWall" : U"JumpToggleWallAlpha")).resized(CHIP_SIZE).draw(pos);
}
