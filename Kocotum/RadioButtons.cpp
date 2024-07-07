#include "RadioButtons.hpp"

/// @brief コンストラクタ
/// @param pos ラジオボタン群の初期位置
/// @param labels 各ラジオボタンのラベルの配列
/// @param index 選択されているラジオボタンのインデックスへの参照
RadioButtons::RadioButtons(Vec2 pos, Array<String> labels, size_t& index)
	: index{ index }
{
	double width = 0;
	for (int i = 0; i < labels.size(); i++)
	{
		// 各ラジオボタンを初期位置に基づいて配置
		buttons << RadioButton(pos + Vec2{ width, 0 }, labels[i]);
		// ボタンの幅を累積
		width += buttons[i].getWidth();
	}

	// 最初のボタンを選択状態に設定
	if (not buttons.isEmpty())
	{
		buttons[0].setSelected(true);
		index = 0;
	}
}

/// @brief 全てのラジオボタンの有効/無効を設定
/// @param enable 有効にする場合はtrue、無効にする場合はfalse
void RadioButtons::setEnable(bool enable)
{
	for (auto& button : buttons)
	{
		button.setEnable(enable);
	}
}

/// @brief ラジオボタンの状態を更新
void RadioButtons::update()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].isEnable())
		{
			// ラジオボタンがクリックされた場合
			if (buttons[i].getButton().leftClicked())
			{
				index = i;
			}

			// 選択状態を更新
			buttons[i].setSelected(index == i);
		}
	}
}

/// @brief ラジオボタンを描画
void RadioButtons::draw() const
{
	for (const auto& button : buttons)
	{
		button.draw();
	}
}
