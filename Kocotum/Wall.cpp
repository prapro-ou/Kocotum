#include "Wall.hpp"

Wall::Wall(Vec2 pos, World& world)
	: Object{ pos, world, U"壁" }
	, body{ RectF{ pos, CHIP_SIZE } }
{
}

void Wall::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool Wall::intersectsPlayer()
{
	return body.intersects(world.player.body);
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
	if (world.player.velocity.x > 0)
	{
		// 右方向に進行中の場合
		world.player.pos.x = pos.x - world.player.body.w;
	}
	else
	{
		// 左方向に進行中の場合
		world.player.pos.x = pos.x + CHIP_SIZE.x;
	}

	world.player.friction = 1.0;
	world.player.velocity.x = 0;
	world.player.body.setPos(world.player.pos);
}

void Wall::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (world.player.isGravityReverse)
	{
		// 重力反転時の処理
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
	else
	{
		// 通常重力時の処理
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

	world.player.friction = 1.0;
	world.player.velocity.y = 0.01;
	world.player.body.setPos(world.player.pos);
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

JumpToggleWall::JumpToggleWall(Vec2 pos, World& world, bool init)
	: Object{ pos, world, U"ジャンプで切り替わる壁" }
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
	return body.intersects(world.player.body);
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
		if (world.player.velocity.x > 0)
		{
			// 右方向に進行中の場合
			world.player.pos.x = pos.x - world.player.body.w;
		}
		else
		{
			// 左方向に進行中の場合
			world.player.pos.x = pos.x + CHIP_SIZE.x;
		}

		world.player.friction = 1.0;
		world.player.velocity.x = 0;
	}

	world.player.body.setPos(world.player.pos);
}

void JumpToggleWall::handleCollisionY()
{
	// 壁がオンの場合のみ衝突処理を行う
	if (isOn)
	{
		// プレイヤーとの垂直方向の衝突処理
		if (world.player.isGravityReverse)
		{
			// 重力反転時の処理
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
		else
		{
			// 通常重力時の処理
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

		world.player.friction = 1.0;
		world.player.velocity.y = 0.01;
	}

	world.player.body.setPos(world.player.pos);
}

void JumpToggleWall::update()
{
	// プレイヤーがジャンプした時に壁の状態を切り替える
	if (world.player.jumpNum < world.player.maxJumpNum && KeySpace.down() && world.player.isAlive)
	{
		isOn = !isOn; // 状態を反転
	}
}

void JumpToggleWall::draw() const
{
	// 壁の状態に応じたテクスチャを描画
	TextureAsset((isOn ? U"JumpToggleWall" : U"JumpToggleWallAlpha")).resized(CHIP_SIZE).draw(pos);
}

IceWall::IceWall(Vec2 pos, World& world)
	: Object{ pos, world, U"氷の壁" }
	, body{ RectF{ pos, CHIP_SIZE } }
{
}

void IceWall::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool IceWall::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool IceWall::mouseOver()
{
	return body.mouseOver();
}

void IceWall::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void IceWall::handleCollisionX()
{
	// プレイヤーとの水平方向の衝突処理
	if (world.player.velocity.x > 0)
	{
		// 右方向に進行中の場合
		world.player.pos.x = pos.x - world.player.body.w;
	}
	else
	{
		// 左方向に進行中の場合
		world.player.pos.x = pos.x + CHIP_SIZE.x;
	}

	world.player.maxSpeed = 500;
	world.player.friction = 0.2;
	world.player.velocity.x = 0;
	world.player.body.setPos(world.player.pos);
}

void IceWall::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (world.player.isGravityReverse)
	{
		// 重力反転時の処理
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
	else
	{
		// 通常重力時の処理
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

	world.player.maxSpeed = 500;
	world.player.friction = 0.2;
	world.player.velocity.y = 0.01;
	world.player.body.setPos(world.player.pos);
}

void IceWall::update()
{
	// 更新処理（現在は何もしない）
}

void IceWall::draw() const
{
	// 壁のテクスチャを描画
	TextureAsset(U"IceWall").resized(CHIP_SIZE).draw(pos);
}

SpeedWall::SpeedWall(Vec2 pos, World& world)
	: Object{ pos, world, U"乗ると加速する壁" }
	, body{ RectF{ pos, CHIP_SIZE } }
{
}

void SpeedWall::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool SpeedWall::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool SpeedWall::mouseOver()
{
	return body.mouseOver();
}

void SpeedWall::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void SpeedWall::handleCollisionX()
{
	// プレイヤーとの水平方向の衝突処理
	if (world.player.velocity.x > 0)
	{
		// 右方向に進行中の場合
		world.player.pos.x = pos.x - world.player.body.w;
	}
	else
	{
		// 左方向に進行中の場合
		world.player.pos.x = pos.x + CHIP_SIZE.x;
	}

	world.player.maxSpeed = 700;
	world.player.friction = 0.01;
	world.player.velocity.x = 0;
	world.player.body.setPos(world.player.pos);
}

void SpeedWall::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (world.player.isGravityReverse)
	{
		// 重力反転時の処理
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
	else
	{
		// 通常重力時の処理
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

	world.player.gif.setActiveKey(U"move");
	world.player.maxSpeed = 700;
	world.player.friction = 0.01;
	world.player.velocity.x = (world.player.isFacingRight ? 1 : -1) * 700;
	world.player.velocity.y = 0.01;
	world.player.body.setPos(world.player.pos);
}

void SpeedWall::update()
{
	// 更新処理（現在は何もしない）
}

void SpeedWall::draw() const
{
	// 壁のテクスチャを描画
	TextureAsset(U"SpeedWall").resized(CHIP_SIZE).draw(pos);
}
