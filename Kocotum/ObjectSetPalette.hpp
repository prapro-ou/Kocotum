#pragma once
#include <Siv3D.hpp>
#include "Effect.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Objects.hpp"
#include "RadioButtons.hpp"
#include "SpinBox.hpp"
#include "TextBox.hpp"

/// @brief オブジェクト設定用のパレットクラス
class ObjectSetPalette
{
public:
	/// @brief パレットの位置
	Vec2 pos;

	/// @brief パレットの本体矩形
	RectF body;

	/// @brief 向きの選択インデックス
	size_t indexDirection;

	/// @brief ジャンプトグルの選択インデックス
	size_t indexJumpToggle;

	/// @brief 向き選択用のラジオボタン
	RadioButtons direction;

	/// @brief ジャンプトグル選択用のラジオボタン
	RadioButtons jumpToggle;

	/// @brief 長さ設定用のSpinBox
	SpinBox length;

	/// @brief テキスト設定用のTextBox
	TextBox text;

	/// @brief ワープポイント用のファイル名
	String fileName;

	/// @brief コンストラクタ
	/// @param pos パレットの位置
	/// @param width パレットの幅
	/// @param height パレットの高さ
	ObjectSetPalette(Vec2 pos, uint32 width = 490, uint32 height = 840);

	/// @brief オブジェクトの設定を読み込む
	/// @param object 設定を読み込むオブジェクト
	void loadSettings(std::shared_ptr<Object>& object);

	/// @brief パレットの状態を更新し、オブジェクトに反映する
	/// @param object 更新するオブジェクト
	void update(std::shared_ptr<Object>& object);

	/// @brief パレットを描画する
	void draw() const;
};
