#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


/// @brief 動く床
struct MoveFloor : public Object
{
	/// @brief 床の当たり判定用の矩形
	RectF body;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 床の動く方向
	E_Direction direction;
	/// @brief 床の動く長さ
	double length;
	/// @brief 床の1フレーム前の座標
	Vec2 previousPos;
	/// @brief 床の元の座標
	Vec2 basePos;
	/// @brief 1フレーム前からの変化量
	Vec2 diff;

	MoveFloor(Vec2 pos, World& world, E_Direction direction = E_Direction::Up, double length = CHIP_SIZE.x * 5);

	void setDirection(E_Direction direction);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
