#include "RadioButtons.hpp"

RadioButtons::RadioButtons(Vec2 pos, Array<String> labels, size_t& index)
	: index{ index }
{
	double width = 0;
	for (int i = 0; i < labels.size(); i++)
	{
		// 各ラジオボタンを作成し、配列に追加
		buttons << RadioButton(pos + Vec2{ width, 0 }, labels[i]);
		width += buttons[i].getWidth();
	}

	if (not buttons.isEmpty())
	{
		// 最初のボタンを選択状態にする
		buttons[0].setSelected(true);
		index = 0;
	}
}

void RadioButtons::setEnable(bool enable)
{
	// 全てのボタンの有効/無効状態を設定
	for (auto& button : buttons)
	{
		button.setEnable(enable);
	}
}

void RadioButtons::update()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].isEnable())
		{
			// ボタンがクリックされた場合、そのインデックスを選択状態にする
			if (buttons[i].getButton().leftClicked())
			{
				index = i;
			}

			// 選択状態を更新
			if (index == i)
			{
				buttons[i].setSelected(true);
			}
			else
			{
				buttons[i].setSelected(false);
			}
		}
	}
}

void RadioButtons::draw() const
{
	// 全てのボタンを描画
	for (auto& button : buttons)
	{
		button.draw();
	}
}
