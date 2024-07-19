# include "MoveFloor.hpp"

MoveFloor::MoveFloor(Vec2 pos, World& world, E_Direction direction, double length)
	:Object{ pos, world, U"動く床" }
	, direction{ direction }
	, length{ length }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ RectF{ pos, CHIP_SIZE.x, CHIP_SIZE.y / 4 } }
	, previousPos{ pos }
	, basePos{ pos }
	, diff{ Vec2{ 0, 0 } }
{
}


void MoveFloor::setDirection(E_Direction direction)
{
	this->direction = direction;
}


void MoveFloor::restart()
{
	
}

bool MoveFloor::intersectsPlayer()
{
	return body.intersects(world.player.body.bottom());
}

bool MoveFloor::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void MoveFloor::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	body.setPos(pos);
	this->pos = pos;
}


void MoveFloor::handleCollisionX()
{
	// x軸方向は衝突判定をしない
}

void MoveFloor::handleCollisionY()
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

			world.player.pos.x += diff.x;

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

			world.player.pos.x += diff.x;

			world.player.velocity.y = 0.01;
		}
	}

	world.player.body.setPos(world.player.pos);
}




void MoveFloor::update()
{
	previousPos = pos;
	Vec2 move{ 0, 0 };
	// 方向が奇数の時(右か左)
	if ((uint16)direction % 2)
	{
		move.x = Periodic::Sine0_1(4s) * length * ((uint16)direction >= 2 ? -1 : 1);
	}
	// 偶数の時(上か下)
	else
	{
		move.y = Periodic::Sine0_1(4s) * length * ((uint16)direction <= 2 ? -1 : 1);
	}

	pos = basePos + move;
	body.setPos(pos);

	diff = pos - previousPos;
}

void MoveFloor::draw() const
{
	TextureAsset(U"MoveFloor").resized(CHIP_SIZE).draw(pos);
}
