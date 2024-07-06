#include "RadioButton.hpp"

RadioButton::RadioButton(Vec2 pos, String label)
	: pos{ pos }
	, button{ Circle{pos + Vec2{ 20, 20 }, 12} }
	, selected{ false }
	, label{ label }
	, body{ RectF{ pos, 50 + SimpleGUI::GetFont()(label).region().w, 40} }
	, enable{ true }
{
	// コンストラクタの初期化
}

void RadioButton::setPos(Vec2 pos)
{
	this->pos = pos;
	button.setPos(pos + Vec2{ 20, 20 }); // ボタンの位置を更新
	body.setPos(pos); // 描画エリアの位置を更新
}

double RadioButton::getWidth()
{
	return body.w; // 描画エリアの幅を返す
}

void RadioButton::setEnable(bool enable)
{
	this->enable = enable; // 有効/無効状態を設定
}

bool RadioButton::isEnable()
{
	return enable; // 現在の有効/無効状態を返す
}

void RadioButton::setSelected(bool selected)
{
	this->selected = selected; // 選択状態を設定
}

bool RadioButton::isSelected()
{
	return selected; // 現在の選択状態を返す
}

Circle RadioButton::getButton()
{
	return button; // ボタン部分のCircleオブジェクトを返す
}

void RadioButton::update()
{
}

void RadioButton::draw() const
{
	// 描画エリアを描画（有効時は白、無効時は銀色）
	body.draw((enable ? Palette::White : Palette::Silver));

	// ボタンの枠を描画（選択時は青、非選択時は灰色）
	button.drawFrame(3, (enable and selected ? Palette::Dodgerblue : Palette::Dimgray));

	// 選択時はボタン内部を塗りつぶす
	if (selected)
	{
		button.stretched(-5).draw(enable ? Palette::Dodgerblue : Palette::Dimgray);
	}

	// ラベルを描画
	SimpleGUI::GetFont()(label).draw(Arg::leftCenter(pos + Vec2{ 40, 20 }), Palette::Black);
}
