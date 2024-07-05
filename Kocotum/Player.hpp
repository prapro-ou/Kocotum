# pragma once
# include <Siv3D.hpp>
# include "Object.hpp"

 /// @brief プレイヤーキャラクターを表す構造体
struct Player
{
	RectF body;             /// プレイヤーの当たり判定用矩形
	Vec2 pos;               /// プレイヤーの現在位置
	Vec2 respawnPos;        /// リスポーン位置
	Vec2 velocity;          /// 速度
	Vec2 accelaration;      /// 加速度
	uint8 jumpNum;          /// 現在のジャンプ回数
	uint8 maxJumpNum;       /// 最大ジャンプ回数
	int8 gravityDirection;  /// 重力の方向
	bool isGravityReverse;  /// 重力反転フラグ
	bool isAlive;           /// 生存フラグ
	bool isOnGround;        /// 地面接地フラグ
	bool isFacingRight;     /// 右向きフラグ

	/**
	 * @brief コンストラクタ
	 * @param pos 初期位置
	 */
	Player(Vec2 pos);

	/// @brief プレイヤーの情報を出力
	void printInfo();

	/// @brief プレイヤーをリスタート位置に戻す
	void restart();

	/**
	 * @brief X軸方向の位置を更新
	 * @param objects ゲーム内のオブジェクト配列
	 */
	void updatePositionX(Array<std::shared_ptr<Object>>& objects);

	/**
	 * @brief Y軸方向の位置を更新
	 * @param objects ゲーム内のオブジェクト配列
	 */
	void updatePositionY(Array<std::shared_ptr<Object>>& objects);

	/**
	 * @brief プレイヤーの状態を更新
	 * @param objects ゲーム内のオブジェクト配列
	 */
	void update(Array<std::shared_ptr<Object>>& objects);

	/// @brief プレイヤーを描画
	void draw() const;
};
