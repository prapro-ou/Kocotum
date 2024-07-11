# pragma once
# include <Siv3D.hpp>

 /// オブジェクトのサイズを定義
const Vec2 CHIP_SIZE = Vec2{ 64, 64 };


/// @brief オブジェクトの種類を表す列挙型
enum class E_ObjectType : uint16
{
	Wall, /// 壁
	JumpToggleWall, /// ジャンプで切り替わる壁
	Needle, /// 針
	MiniNeedle, /// 小さい針
	JumpToggleNeedle, /// ジャンプで切り替わる針
	GravityLineHorizontal, /// 水平重力線
	GravityLineVertical, /// 垂直重力線
	MoveFloorHorizontal, /// 水平移動床
	MoveFloorVertical, /// 垂直移動床
	StartPoint, /// スタート地点
	SavePoint, /// セーブポイント
	Text, /// ゲーム内に表示するテキスト
	Image, /// ゲーム内に表示する画像
	WarpPoint, /// ワープポイント
	OneWayFloor, /// 足場
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
class World;

/// @brief マップ上に配置されているオブジェクトの基底クラス
struct Object
{
	Vec2 pos;               /// オブジェクトの位置
	World& world;			/// プレイヤー参照
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
	Object(Vec2 pos, World& world, E_ObjectType type, String name)
		: pos{ pos }
		, world{ world }
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
