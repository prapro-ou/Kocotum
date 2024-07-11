#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


struct WarpPoint : public Object
{
	RectF body; ///< 壁の当たり判定用の矩形
	String fileName;

	WarpPoint(Vec2 pos, World& world, String fileName = U"");

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
