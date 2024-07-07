#pragma once
#include <Siv3D.hpp>
#include "RadioButton.hpp"

/**
 * @class RadioButtons
 * @brief 複数のラジオボタンを管理するクラス
 */
class RadioButtons
{
private:
	/// @brief ラジオボタンの配列
	Array<RadioButton> buttons;
	/// @brief 現在選択されているラジオボタンのインデックス
	size_t& index;

public:
	/**
	 * @brief コンストラクタ
	 * @param pos ラジオボタン群の初期位置
	 * @param labels 各ラジオボタンのラベルの配列
	 * @param index 選択されているラジオボタンのインデックスへの参照
	 */
	RadioButtons(Vec2 pos, Array<String> labels, size_t& index);

	/**
	 * @brief 全てのラジオボタンの有効/無効を設定
	 * @param enable 有効にする場合はtrue、無効にする場合はfalse
	 */
	void setEnable(bool enable);

	/**
	 * @brief ラジオボタンの状態を更新
	 */
	void update();

	/**
	 * @brief ラジオボタンを描画
	 */
	void draw() const;
};
