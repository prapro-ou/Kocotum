# include "Spring.hpp"


Spring::Spring(Vec2 pos, World& world)
	:Object{ pos, world, U"ばね" }
	, body{ RectF{ pos, CHIP_SIZE } }
{ }


void Spring::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool Spring::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool Spring::mouseOver()
{
	return body.mouseOver();
}

void Spring::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void Spring::handleCollisionX()
{
	// プレイヤーとの水平方向の衝突処理
	if (world.player.velocity.x > 0)
	{
		// 右方向に進行中の場合
		world.player.velocity.x = -world.player.maxSpeed * 2;
		world.player.pos.x = pos.x - world.player.body.w;
	}
	else
	{
		// 左方向に進行中の場合
		world.player.velocity.x = world.player.maxSpeed * 2;
		world.player.pos.x = pos.x + CHIP_SIZE.x;
	}

	world.player.body.setPos(world.player.pos);
}

void Spring::handleCollisionY()
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

void Spring::update()
{

}

void Spring::draw() const
{
	body.draw(Palette::Aqua);
}
