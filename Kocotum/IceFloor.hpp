#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"

/**
 * @brief 滑る床オブジェクトを表すクラス
 */
struct IceFloor : public Object
{
	/// @brief 滑る床の当たり判定用の矩形
	RectF body;

	///// @brief マウス判定用の矩形
	//rectf mouseoverbody;

	///// @brief 床の動く方向
	//E_Direction direction;

	/**
	 * @brief IceFloorクラスのコンストラクタ
	 * @param pos 滑る床の位置
	 */
	IceFloor(Vec2 pos, World& world);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
