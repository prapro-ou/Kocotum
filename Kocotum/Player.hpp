# pragma once
# include <Siv3D.hpp>
# include "Object.hpp"
# include "GIF.hpp"

 /// @brief プレイヤーキャラクターを表す構造体
struct Player
{
	/// @brief プレイヤーの当たり判定用矩形
	RectF body;
	/// @brief プレイヤーの現在位置
	Vec2 pos;
	/// @brief プレイヤーのリスポーン位置
	Vec2 respawnPos;
	/// @brief プレイヤーの速度
	Vec2 velocity;
	/// @brief プレイヤーの加速度
	Vec2 accelaration;
	/// @brief プレイヤーの横方向の最大速度
	double maxSpeed;
	/// @brief 現在のジャンプ回数
	uint8 jumpNum;
	/// @brief 最大ジャンプ回数
	uint8 maxJumpNum;
	/// @brief 重力の方向
	int8 gravityDirection;
	/// @brief 重力反転フラグ
	bool isGravityReverse;
	/// @brief 生存フラグ
	bool isAlive;
	/// @brief 地面接地フラグ
	bool isOnGround;
	/// @brief 右向きフラグ
	bool isFacingRight;
	/// @brief ワープ発生フラグ
	bool causeWarp;
	/// @brief 摩擦係数
	double friction;
	/// @brief 摩擦で止まる動作用のdouble
	double velocityFriction;
	/// @brief 最大スピードに抑える用のdouble
	double velocityClamp;
	/// @brief 身体の倍率
	double scale;

	GIFManager gif;

	/**
	 * @brief コンストラクタ
	 * @param pos 初期位置
	 */
	Player(Vec2 pos);

	/// @brief プレイヤーの情報を出力
	void printInfo();

	/// @brief プレイヤーをリスタート位置に戻す
	void restart();

	void setPos(Vec2 pos)
	{
		this->pos = pos;
	}

	void setFriction(double friction)
	{
		this->friction = friction;
	}

	void setVelocity(Vec2 velocity)
	{
		this->velocity = velocity;
	}

	void setScale(double scale)
	{
		this->scale = scale;
		body.setSize(Vec2{ 25, 35 } * scale);
	}

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
