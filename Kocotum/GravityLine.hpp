#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"

/**
 * @brief 横方向の重力線オブジェクトを表すクラス
 */
struct GravityLineHorizontal : public Object
{
	bool isTouched; ///< プレイヤーが触れたかどうか
	double length; ///< 重力線の長さ
	RectF mouseOverBody; ///< マウスオーバー判定用の矩形
	RectF body; ///< 重力線の当たり判定用の矩形

	/**
	 * @brief GravityLineHorizontalクラスのコンストラクタ
	 * @param pos 重力線の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param length 重力線の長さ（デフォルトはCHIP_SIZE.x）
	 */
	GravityLineHorizontal(Vec2 pos, World& world, double length = CHIP_SIZE.x);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};

/**
 * @brief 縦方向の重力線オブジェクトを表すクラス
 */
struct GravityLineVertical : public Object
{
	bool isTouched; ///< プレイヤーが触れたかどうか
	double length; ///< 重力線の長さ
	RectF mouseOverBody; ///< マウスオーバー判定用の矩形
	RectF body; ///< 重力線の当たり判定用の矩形

	/**
	 * @brief GravityLineVerticalクラスのコンストラクタ
	 * @param pos 重力線の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param length 重力線の長さ（デフォルトはCHIP_SIZE.y）
	 */
	GravityLineVertical(Vec2 pos, World& world, double length = CHIP_SIZE.y);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
