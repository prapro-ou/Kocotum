/** @file Object.hpp
 *  @brief ゲーム内オブジェクトの基底クラスと関連する定義を含むヘッダファイル
 */

# pragma once
# include <Siv3D.hpp>

 /// オブジェクトのサイズを定義
const Vec2 CHIP_SIZE = Vec2{ 64, 64 };

/// @name オブジェクトの属性を表すビットフラグ
///@{
const uint16 isWall = 0b00000100;
const uint16 isNeedle = 0b00001000;
const uint16 isJumpToggle = 0b00010000;
const uint16 hasLength = 0b00100000;
///@}

/// @brief オブジェクトの種類を表す列挙型
enum class E_ObjectType : uint16
{
	Wall					= 0b00000100, /// 壁
	JumpToggleWall			= 0b00010100, /// ジャンプで切り替わる壁
	Needle					= 0b00001000, /// 針
	MiniNeedle				= 0b00001001, /// 小さい針
	JumpToggleNeedle		= 0b00011000, /// ジャンプで切り替わる針
	GravityLineHorizontal	= 0b00100000, /// 水平重力線
	GravityLineVertical		= 0b00100001, /// 垂直重力線
	MoveFloorHorizontal		= 0b01100000, /// 水平移動床
	MoveFloorVertical		= 0b01100001, /// 垂直移動床
};

/// @brief 方向を表す列挙型
enum class E_Direction : uint16
{
	Up,    /// 上
	Right, /// 右
	Down,  /// 下
	Left,  /// 左
};

/// 前方宣言
struct Player;

/// @brief マップ上に配置されているオブジェクトの基底クラス
struct Object
{
	Vec2 pos;               /// オブジェクトの位置
	Effect& effect;         /// エフェクト参照
	Player& player;         /// プレイヤー参照
	E_ObjectType type;      /// オブジェクトの種類
	String name;            /// オブジェクトの名前

	/**
	 * @brief コンストラクタ
	 * @param pos オブジェクトの初期位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param type オブジェクトの種類
	 * @param name オブジェクトの名前
	 */
	Object(Vec2 pos, Effect& effect, Player& player, E_ObjectType type, String name)
		: pos{ pos }
		, effect{ effect }
		, player{ player }
		, type{ type }
		, name{ name }
	{ }

	/// @brief オブジェクトのリスタート
	virtual void restart() = 0;

	/// @brief プレイヤーとの衝突判定
	/// @return プレイヤーと衝突していればtrue、そうでなければfalse
	virtual bool intersectsPlayer() = 0;

	/// @brief マウスオーバー判定
	/// @return マウスがオブジェクト上にあればtrue、そうでなければfalse
	virtual bool mouseOver() = 0;

	/// @brief 位置の設定
	/// @param newPos 新しい位置
	virtual void setPos(Vec2 newPos) = 0;

	/// @brief X軸方向の衝突処理
	virtual void handleCollisionX() = 0;

	/// @brief Y軸方向の衝突処理
	virtual void handleCollisionY() = 0;

	/// @brief 更新処理
	virtual void update() = 0;

	/// @brief 描画処理
	virtual void draw() const = 0;
};
