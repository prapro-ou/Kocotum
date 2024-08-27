# include "TouchActiveFloor.hpp"

TouchActiveFloor::TouchActiveFloor(Vec2 pos, World& world, E_Direction direction, double length)
	:Object{ pos, world, U"乗ると動く床" }
	, direction{ direction }
	, length{ length }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE.x * 2, CHIP_SIZE.y } }
	, body{ RectF{ pos, CHIP_SIZE.x * 2, CHIP_SIZE.y / 2 } }
	, previousPos{ pos }
	, basePos{ pos }
	, diff{ Vec2{ 0, 0 } }
	, isTouched{ false }
	, isInversion{ false }
{
}


void TouchActiveFloor::setDirection(E_Direction direction)
{
	this->direction = direction;
}


void TouchActiveFloor::restart()
{
	pos = basePos;
	isTouched = false;
	isInversion = false;
}

bool TouchActiveFloor::intersectsPlayer()
{
	if (world.player.isGravityReverse)
	{
		return body.intersects(world.player.body.top());
	}
	else
	{
		return body.intersects(world.player.body.bottom());
	}
}

bool TouchActiveFloor::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void TouchActiveFloor::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	body.setPos(pos);
	this->pos = pos;
}


void TouchActiveFloor::handleCollisionX()
{

}

void TouchActiveFloor::handleCollisionY()
{
	// プレイヤーとの垂直方向の衝突処理
	if (world.player.isGravityReverse)
	{
		// 重力反転時の処理
		if (world.player.velocity.y > 0)
		{
			isTouched = true;

			world.player.pos.y = pos.y + CHIP_SIZE.y / 2.1;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;

			world.player.pos.x += diff.x;

			world.player.friction = 1.0;
			world.player.velocity.y = 0.01;
		}
	}
	else
	{
		// 通常重力時の処理
		if (world.player.velocity.y > 0)
		{
			isTouched = true;

			world.player.pos.y = pos.y - world.player.body.h;
			world.player.jumpNum = 0;
			world.player.isOnGround = true;

			world.player.pos.x += diff.x;

			world.player.friction = 1.0;
			world.player.velocity.y = 0.01;
		}
	}

	world.player.body.setPos(world.player.pos);
}




void TouchActiveFloor::update()
{
	previousPos = pos;
	Vec2 move{ 0, 0 };

	// 到達したら反転
	if (isInversion)
	{
		if (direction == E_Direction::Up)
		{
			if (pos.y >= basePos.y)
			{
				isInversion = false;
			}
		}
		else if (direction == E_Direction::Right)
		{
			if (pos.x <= basePos.x)
			{
				isInversion = false;
			}
		}
		else if (direction == E_Direction::Down)
		{
			if (pos.y <= basePos.y)
			{
				isInversion = false;
			}
		}
		else if (direction == E_Direction::Left)
		{
			if (pos.x <= basePos.x)
			{
				isInversion = false;
			}
		}
	}
	else
	{
		if (direction == E_Direction::Up)
		{
			if (pos.y <= basePos.y - length)
			{
				isInversion = true;
			}
		}
		else if (direction == E_Direction::Right)
		{
			if (pos.x >= basePos.x + length)
			{
				isInversion = true;
			}
		}
		else if (direction == E_Direction::Down)
		{
			if (pos.y >= basePos.y + length)
			{
				isInversion = true;
			}
		}
		else if (direction == E_Direction::Left)
		{
			if (pos.x >= basePos.x + length)
			{
				isInversion = true;
			}
		}
	}

	if (isTouched)
	{
		// 方向が奇数の時(右か左)
		if ((uint16)direction % 2)
		{
			pos.x += CHIP_SIZE.x * 3 * ((uint16)direction >= 2 ? -1 : 1) * (isInversion ? -1 : 1) * Scene::DeltaTime();
		}
		// 偶数の時(上か下)
		else
		{
			pos.y += CHIP_SIZE.y * 3 * ((uint16)direction <= 2 ? -1 : 1) * (isInversion ? -1 : 1) * Scene::DeltaTime();
		}

		diff = pos - previousPos;

		if (diff.y > 0)
		{
			world.player.pos.y += diff.y;
		}
	}

	body.setPos(pos);

	if (!world.player.body.intersects(body))
	{
		isTouched = false;
	}

	diff = pos - previousPos;
}

void TouchActiveFloor::draw() const
{
	if (isTouched)
	{
		TextureAsset(U"TouchActiveFloorActive").resized(CHIP_SIZE.x * 2, CHIP_SIZE.y / 2).draw(pos);
	}
	else
	{
		TextureAsset(U"TouchActiveFloor").resized(CHIP_SIZE.x * 2, CHIP_SIZE.y / 2).draw(pos);
	}
}
