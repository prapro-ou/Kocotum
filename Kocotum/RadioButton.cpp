#include "RadioButton.hpp"

/// @brief コンストラクタ
/// @param pos ラジオボタンの位置
/// @param label ラジオボタンのラベル（デフォルトは空文字）
RadioButton::RadioButton(Vec2 pos, String label)
	: pos{ pos }
	, button{ Circle{ pos + Vec2{ 20, 20 }, 12 } }
	, selected{ false }
	, label{ label }
	, body{ RectF{ pos, 50 + SimpleGUI::GetFont()(label).region().w, 40 } }
	, enable{ true }
{
	// コンストラクタの内部処理
}

/// @brief ラジオボタンの位置を設定
/// @param pos 新しい位置
void RadioButton::setPos(Vec2 pos)
{
	this->pos = pos;
	button.setPos(pos + Vec2{ 20, 20 });
	body.setPos(pos);
}

/// @brief ラジオボタンの幅を取得
/// @return ラジオボタンの幅
double RadioButton::getWidth()
{
	return body.w;
}

/// @brief ラジオボタンの有効/無効を設定
/// @param enable 有効にする場合はtrue、無効にする場合はfalse
void RadioButton::setEnable(bool enable)
{
	this->enable = enable;
}

/// @brief ラジオボタンが有効かどうかを確認
/// @return 有効な場合はtrue、無効な場合はfalse
bool RadioButton::isEnable()
{
	return enable;
}

/// @brief ラジオボタンの選択状態を設定
/// @param selected 選択状態にする場合はtrue、解除する場合はfalse
void RadioButton::setSelected(bool selected)
{
	this->selected = selected;
}

/// @brief ラジオボタンが選択されているかどうかを確認
/// @return 選択されている場合はtrue、されていない場合はfalse
bool RadioButton::isSelected()
{
	return selected;
}

/// @brief ラジオボタンのボタン部分を取得
/// @return ラジオボタンのボタン部分
Circle RadioButton::getButton()
{
	return button;
}

/// @brief ラジオボタンの状態を更新
void RadioButton::update()
{

}

/// @brief ラジオボタンを描画
void RadioButton::draw() const
{
	body.draw((enable ? Palette::White : Palette::Silver));
	button.drawFrame(3, (enable && selected ? Palette::Dodgerblue : Palette::Dimgray));
	if (selected)
	{
		button.stretched(-5).draw(enable ? Palette::Dodgerblue : Palette::Dimgray);
	}
	SimpleGUI::GetFont()(label).draw(Arg::leftCenter(pos + Vec2{ 40, 20 }), Palette::Black);
}
