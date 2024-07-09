#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


struct StartPoint : public Object
{
	RectF body; /// 当たり判定用の矩形


	StartPoint(Vec2 pos, World& world)
		:Object{ pos, world, E_ObjectType::StartPoint, U"スタート位置" }
		, body{ RectF{ pos, CHIP_SIZE } }
	{ }

	void restart() override
	{
	}

	bool intersectsPlayer() override
	{
		return false;
		//return body.intersects(world.player.body);
	}

	bool mouseOver() override
	{
		return body.mouseOver();
	}

	void setPos(Vec2 pos) override
	{
		this->pos = pos;
		body.setPos(pos);
	}
	void handleCollisionX() override
	{

	}

	void handleCollisionY() override
	{

	}

	void update() override
	{

	}

	void draw() const override
	{
		body.draw(ColorF(0.25, 0.5, 0.5, 0.25));
	}
};
