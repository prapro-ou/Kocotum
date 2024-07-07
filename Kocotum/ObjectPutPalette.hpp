#pragma once
#include <Siv3D.hpp>
#include "Effect.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Objects.hpp"
#include "SelectObjectWindow.hpp"

/// @brief オブジェクト配置用のパレットクラス
class ObjectPutPalette
{
public:
	/// @brief パレットの位置
	Vec2 pos;

	/// @brief パレットの本体描画用テクスチャ
	MSRenderTexture body;

	/// @brief オブジェクト選択ウィンドウの配列
	Array<SelectObjectWindow> windows;

	/// @brief エフェクト
	Effect effect;

	/// @brief プレイヤー
	Player player;

	/// @brief コンストラクタ
	/// @param pos パレットの位置
	/// @param width パレットの幅
	/// @param height パレットの高さ
	ObjectPutPalette(Vec2 pos, uint32 width = 490, uint32 height = 840);

	/// @brief クリックされたオブジェクトタイプを取得する
	/// @return クリックされたオブジェクトタイプ（Optional）
	Optional<E_ObjectType> getClickedType();

	/// @brief パレットの状態を更新する
	void update();

	/// @brief パレットを描画する
	void draw() const;
};
