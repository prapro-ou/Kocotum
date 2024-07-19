#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"

/**
 * @brief 壁オブジェクトを表すクラス
 */
struct Wall : public Object
{
	RectF body; ///< 壁の当たり判定用の矩形

	/**
	 * @brief Wallクラスのコンストラクタ
	 * @param pos 壁の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 */
	Wall(Vec2 pos, World& world);

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
 * @brief ジャンプで切り替わる壁オブジェクトを表すクラス
 */
struct JumpToggleWall : public Object
{
	RectF body; ///< 壁の当たり判定用の矩形
	bool init; ///< 初期状態
	bool isOn; ///< 現在の状態（オン/オフ）

	/**
	 * @brief JumpToggleWallクラスのコンストラクタ
	 * @param pos 壁の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param init 初期状態（デフォルトはtrue）
	 */
	JumpToggleWall(Vec2 pos, World& world, bool init = true);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;

	/**
	 * @brief 初期状態を設定する
	 * @param init 設定する初期状態
	 */
	void setInit(bool init);

	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};

/**
 * @brief 氷の壁オブジェクトを表すクラス
 */
struct IceWall : public Object
{
	RectF body; ///< 壁の当たり判定用の矩形

	/**
	 * @brief Wallクラスのコンストラクタ
	 * @param pos 壁の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 */
	IceWall(Vec2 pos, World& world);

	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
