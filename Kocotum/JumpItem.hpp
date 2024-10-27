#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


struct JumpItem : public Object
{
	/// @brief 取得したか
	bool isGot = false;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 当たり判定用の矩形
	Polygon body;
	/// @brief アイテム復活用タイマー
	Stopwatch sw;

	JumpItem(Vec2 pos, World& world);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
