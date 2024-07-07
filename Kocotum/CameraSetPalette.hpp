#pragma once
#include <Siv3D.hpp>
#include "Effect.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Objects.hpp"
#include "RadioButtons.hpp"
#include "SpinBox.hpp"
#include "GameCamera.hpp"

/// @brief カメラ設定用のパレットクラス
class CameraSetPalette
{
public:
	/// @brief パレットの位置
	Vec2 pos;

	/// @brief パレットの本体矩形
	RectF body;

	/// @brief X座標設定用のSpinBox
	SpinBox posX;

	/// @brief Y座標設定用のSpinBox
	SpinBox posY;

	/// @brief 幅設定用のSpinBox
	SpinBox width;

	/// @brief 高さ設定用のSpinBox
	SpinBox height;

	/// @brief 初期X座標設定用のSpinBox
	SpinBox initX;

	/// @brief 初期Y座標設定用のSpinBox
	SpinBox initY;

	/// @brief スケール設定用のSpinBox
	SpinBox scale;

	/// @brief スクロール設定用のラジオボタンのインデックス
	size_t indexScroll;

	/// @brief スクロール設定用のラジオボタン
	RadioButtons scroll;

	/// @brief X方向スクロール速度設定用のSpinBox
	SpinBox velocityX;

	/// @brief Y方向スクロール速度設定用のSpinBox
	SpinBox velocityY;

	/// @brief コンストラクタ
	/// @param pos パレットの位置
	/// @param width パレットの幅
	/// @param height パレットの高さ
	CameraSetPalette(Vec2 pos, uint32 width = 490, uint32 height = 840);

	/// @brief カメラエリアの設定を読み込む
	/// @param area カメラエリアへの共有ポインタ
	void loadSettings(std::shared_ptr<CameraArea>& area);

	/// @brief パレットの状態を更新し、カメラエリアに反映する
	/// @param area カメラエリアへの共有ポインタ
	void update(std::shared_ptr<CameraArea>& area);

	/// @brief パレットを描画する
	void draw() const;

private:

};
