# pragma once
# include <Siv3D.hpp>

 /// オブジェクトのサイズを定義
const Vec2 CHIP_SIZE = Vec2{ 64, 64 };


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
	String name;            /// オブジェクトの名前
	size_t textureIndex;	/// 描画するテクスチャの番号

	/**
	 * @brief コンストラクタ
	 * @param pos オブジェクトの初期位置
	 * @param effect エフェクト参照
	 * @param player プレイヤー参照
	 * @param type オブジェクトの種類
	 * @param name オブジェクトの名前
	 */
	Object(Vec2 pos, World& world, String name, size_t textureIndex = 1)
		: pos{ pos }
		, world{ world }
		, name{ name }
		, textureIndex{ textureIndex }
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
