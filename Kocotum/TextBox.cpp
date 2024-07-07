# include "TextBox.hpp"


TextBox::TextBox(Vec2 pos, double width, uint16 fontSize, String value)
{
	this->pos = pos;
	this->width = Max(width, 50.0);
	this->fontSize = fontSize;
	this->font = Font(fontSize, Typeface::Regular);
	this->height = font.fontSize() * 1.5;
	this->region = RectF(pos, width, height);
	this->value = value;
	this->editingText = U"";
	this->isActive = false;
}


String TextBox::getText()
{
	return value;
}


void TextBox::setText(String text)
{
	this->value = text;
}

void TextBox::update()
{
	// 領域がクリックされていたらアクティブ
	if (MouseL.down())
	{
		isActive = region.mouseOver();
	}

	if (isActive)
	{
		// キーボードからテキストを入力
		TextInput::UpdateText(value);

		// 未変換の文字入力を取得
		editingText = TextInput::GetEditingText();
	}
}

void TextBox::draw() const
{
	region.draw().drawFrame(2, (isActive ? Palette::Dodgerblue : Palette::Dimgray));
	String tmp = U"";
	if (isActive)
	{
		tmp = value + U'|' + editingText;
	}
	else
	{
		tmp = value + editingText;
	}
	font(tmp).draw(region, Palette::Black);
}
