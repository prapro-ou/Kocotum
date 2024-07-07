#pragma once
#include <Siv3D.hpp>
#include "Effect.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Objects.hpp"
#include "World.hpp"
#include "RadioButtons.hpp"
#include "SpinBox.hpp"

/// @brief ワールド編集用のパレットクラス
class WorldEditPalette
{
public:
	/// @brief パレットの位置
	Vec2 pos;

	/// @brief パレットの本体矩形
	RectF body;

	/// @brief コンストラクタ
	/// @param pos パレットの位置
	/// @param width パレットの幅
	/// @param height パレットの高さ
	WorldEditPalette(Vec2 pos, uint32 width = 490, uint32 height = 840);

	/// @brief パレットの状態を更新し、ワールドに反映する
	/// @param world 更新するワールド
	void update(World& world);

	/// @brief パレットを描画する
	void draw() const;
};
