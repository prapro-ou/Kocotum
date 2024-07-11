#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


struct OneWayFloor : public Object
{
	RectF body; /// 当たり判定用の矩形
	RectF mouseOverBody;

	OneWayFloor(Vec2 pos, World& world);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
