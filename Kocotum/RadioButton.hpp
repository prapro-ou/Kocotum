#pragma once
#include <Siv3D.hpp>

/**
 * @class RadioButton
 * @brief ラジオボタンを表すクラス
 */
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
	/**
	 * @brief コンストラクタ
	 * @param pos ラジオボタンの位置
	 * @param label ラジオボタンのラベル（デフォルトは空文字）
	 */
	RadioButton(Vec2 pos, String label = U"");

	/**
	 * @brief ラジオボタンの位置を設定
	 * @param pos 新しい位置
	 */
	void setPos(Vec2 pos);

	/**
	 * @brief ラジオボタンの幅を取得
	 * @return ラジオボタンの幅
	 */
	double getWidth();

	/**
	 * @brief ラジオボタンの有効/無効を設定
	 * @param enable 有効にする場合はtrue、無効にする場合はfalse
	 */
	void setEnable(bool enable);

	/**
	 * @brief ラジオボタンが有効かどうかを確認
	 * @return 有効な場合はtrue、無効な場合はfalse
	 */
	bool isEnable();

	/**
	 * @brief ラジオボタンの選択状態を設定
	 * @param selected 選択状態にする場合はtrue、解除する場合はfalse
	 */
	void setSelected(bool selected);

	/**
	 * @brief ラジオボタンが選択されているかどうかを確認
	 * @return 選択されている場合はtrue、されていない場合はfalse
	 */
	bool isSelected();

	/**
	 * @brief ラジオボタンのボタン部分を取得
	 * @return ラジオボタンのボタン部分
	 */
	Circle getButton();

	/**
	 * @brief ラジオボタンの状態を更新
	 */
	void update();

	/**
	 * @brief ラジオボタンを描画
	 */
	void draw() const;
};
