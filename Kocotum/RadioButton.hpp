#pragma once
#include <Siv3D.hpp>

/// @brief ラジオボタンを表現するクラス
class RadioButton
{
private:
	/// @brief ラジオボタンの座標
	Vec2 pos;

	/// @brief ラジオボタンの描画エリア
	RectF body;

	/// @brief ラジオボタンのボタン部分
	Circle button;

	/// @brief ラジオボタンが押されたかどうか
	bool selected;

	/// @brief ラジオボタンのテキスト
	String label;

	/// @brief 利用可能かどうか
	bool enable;

public:
	/// @brief ラジオボタンのコンストラクタ
	/// @param pos ラジオボタンの座標
	/// @param label ラジオボタンのラベル（デフォルトは空文字）
	RadioButton(Vec2 pos, String label = U"");

	/// @brief ラジオボタンの位置を設定する
	/// @param pos 新しい座標
	void setPos(Vec2 pos);

	/// @brief ラジオボタンの幅を取得する
	/// @return ラジオボタンの幅
	double getWidth();

	/// @brief ラジオボタンの有効/無効を設定する
	/// @param enable 有効にする場合はtrue、無効にする場合はfalse
	void setEnable(bool enable);

	/// @brief ラジオボタンが有効かどうかを確認する
	/// @return 有効な場合はtrue、無効な場合はfalse
	bool isEnable();

	/// @brief ラジオボタンの選択状態を設定する
	/// @param selected 選択状態にする場合はtrue、それ以外はfalse
	void setSelected(bool selected);

	/// @brief ラジオボタンが選択されているかどうかを確認する
	/// @return 選択されている場合はtrue、それ以外はfalse
	bool isSelected();

	/// @brief ラジオボタンのボタン部分を取得する
	/// @return ボタン部分を表すCircleオブジェクト
	Circle getButton();

	/// @brief ラジオボタンの状態を更新する
	void update();

	/// @brief ラジオボタンを描画する
	void draw() const;
};
