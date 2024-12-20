﻿#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


struct GoalPoint : public Object
{
	RectF body; ///< 壁の当たり判定用の矩形
	bool isTouched;

	AnimatedGIFReader gif;
	Array<Image> images;
	Array<int32> delays;
	Array<Texture> textures;

	GoalPoint(Vec2 pos, World& world);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
