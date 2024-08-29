#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"

/**
 * @brief 針オブジェクトを表すクラス
 */
struct Needle : public Object
{
	/// @brief 針の向き
	E_Direction direction;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 針の当たり判定用の三角形
	Triangle body;

	/**
	 * @brief Needleクラスのコンストラクタ
	 * @param pos 針の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param direction 針の向き（デフォルトは上向き）
	 */
	Needle(Vec2 pos, World& world, E_Direction direction = E_Direction::Up, size_t textureIndex = 1);

	/**
	 * @brief 針の向きを設定する
	 * @param direction 設定する向き
	 */
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

/**
 * @brief 小さい針オブジェクトを表すクラス
 */
struct MiniNeedle : public Object
{
	/// @brief 針の向き
	E_Direction direction;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 針の当たり判定用の三角形
	Array<Triangle> body;

	/**
	 * @brief MiniNeedleクラスのコンストラクタ
	 * @param pos 針の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param direction 針の向き（デフォルトは上向き）
	 */
	MiniNeedle(Vec2 pos, World& world, E_Direction direction = E_Direction::Up);

	/**
	 * @brief 針の向きを設定する
	 * @param direction 設定する向き
	 */
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

/**
 * @brief ジャンプで切り替わる針オブジェクトを表すクラス
 */
struct JumpToggleNeedle : public Object
{
	/// @brief 針の向き
	E_Direction direction;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 針の当たり判定用の三角形
	Triangle body;
	/// @brief 出現の初期状態
	bool init;
	/// @brief 現在の状態
	bool isOn;

	/**
	 * @brief JumpToggleNeedleクラスのコンストラクタ
	 * @param pos 針の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param init 初期状態
	 * @param direction 針の向き（デフォルトは上向き）
	 */
	JumpToggleNeedle(Vec2 pos, World& world, bool init = true, E_Direction direction = E_Direction::Up);

	/**
	 * @brief 針の向きを設定する
	 * @param direction 設定する向き
	 */
	void setDirection(E_Direction direction);

	/**
	 * @brief 初期状態を設定する
	 * @param init 設定する初期状態
	 */
	void setInit(bool init);

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
 * @brief 四分の一サイズの針オブジェクトを表すクラス
 */
struct QuarterNeedle : public Object
{
	/// @brief 針の向き
	E_Direction direction;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 針の当たり判定用の三角形
	Triangle body;

	/**
	 * @brief Needleクラスのコンストラクタ
	 * @param pos 針の位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param direction 針の向き（デフォルトは上向き）
	 */
	QuarterNeedle(Vec2 pos, World& world, E_Direction direction = E_Direction::Up, size_t textureIndex = 1);

	/**
	 * @brief 針の向きを設定する
	 * @param direction 設定する向き
	 */
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
