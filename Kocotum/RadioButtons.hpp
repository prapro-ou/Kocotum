#pragma once
#include <Siv3D.hpp>
#include "RadioButton.hpp"

/// @brief 複数のラジオボタンをグループ化して管理するクラス
class RadioButtons
{
private:
	/// @brief ラジオボタンの配列
	Array<RadioButton> buttons;

	/// @brief 選択されているボタンのインデックスへの参照
	size_t& index;

public:
	/// @brief RadioButtonsのコンストラクタ
	/// @param pos グループの開始位置
	/// @param labels 各ラジオボタンのラベル
	/// @param index 選択されているボタンのインデックスへの参照
	RadioButtons(Vec2 pos, Array<String> labels, size_t& index);

	/// @brief 全てのラジオボタンの有効/無効を設定する
	/// @param enable 有効にする場合はtrue、無効にする場合はfalse
	void setEnable(bool enable);

	/// @brief ラジオボタングループの状態を更新する
	void update();

	/// @brief ラジオボタングループを描画する
	void draw() const;
};
