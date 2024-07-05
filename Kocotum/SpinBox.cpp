# include "SpinBox.hpp"

String SpinBox::deleteCursorPosText()
{
	if (value.cursorPos != 0)
	{
		String prevText = value.text.substr(0, value.cursorPos - 1);
		String nextText = value.text.substr(value.cursorPos, value.text.size());

		return prevText + nextText;
	}

	return U"";
}

SpinBox::SpinBox(Vec2 pos, double width, uint16 fontSize, uint32 maxDigit, String value)
{
	this->pos = pos;
	this->width = Max(width, MinWidth);
	this->fontSize = fontSize;
	this->font = Font(fontSize, Typeface::Regular);
	this->height = font.fontSize();
	this->region = RectF(pos, width, height);
	this->value.text = value;
	this->maxDigit = maxDigit;
	this->showCursor = false;
	this->backspaceStopwatch.start();
	this->enable = true;
}

TextEditState& SpinBox::getState()
{
	return value;
}

uint32 SpinBox::getValue()
{
	return ParseOr<uint32>(value.text, 0);
}

void SpinBox::setEnable(bool enable)
{
	this->enable = enable;
}

bool SpinBox::isEnable()
{
	return this->enable;
}

void SpinBox::setValue(double value)
{
	this->value.text = Format(value);
}

void SpinBox::setPos(Vec2 pos)
{
	this->pos = pos;
	this->region.setPos(pos);
}

bool SpinBox::isActive()
{
	return this->value.active;
}

void SpinBox::update()
{
	//クリックされたら
	if (MouseL.down())
	{
		//スピンボックスをクリックしていたらアクティブ
		if (region.mouseOver())
		{
			value.active = true;
			value.cursorPos = value.text.size();

			//カーソル点滅用のストップウォッチをリセット
			value.cursorStopwatch.restart();
			value.leftPressStopwatch.restart();
			value.rightPressStopwatch.restart();
			//文字消去用のストップウォッチをリセット
			backspaceStopwatch.restart();
		}
		//スピンボックスの外ならアクティブでない
		else
		{
			value.active = false;
		}
	}

	//利用可能かつアクティブなら
	if (enable and value.active)
	{
		//キー入力
		String input = TextInput::GetRawInput();

		//入力されたらカーソル点滅リセット
		if (!input.isEmpty()) value.cursorStopwatch.restart();

		//入力が数値変換できるものならば反映
		if (ParseOpt<uint32>(input))
		{
			//現在の値と入力された値を足して最大桁数を越えなければ反映
			if (maxDigit >= value.text.size() + input.size())
			{
				//現在の値がU"0"なら入力をそのまま値にする
				if (value.text == U"0")
				{
					value.text = input;
					value.cursorPos = 0;
				}
				else
				{
					//カーソル位置に入力を挿入する
					value.text.insert(value.cursorPos, input);
				}
				//カーソルの位置を入力分移動させる
				value.cursorPos += input.size();
			}
		}

		//クリックによるカーソルの変更
		for (int i = 0; i < value.text.size(); i++)
		{
			//数字がクリックされたら
			if (font(value.text[i]).region(pos.x + font(value.text[i]).region().w * i, region.pos.y - 5).leftClicked())
			{
				//クリックした数字の左側なら
				if (Cursor::PosF().x < pos.x + font(value.text[i]).region().w * i + font(value.text[i]).region().centerX())
				{
					value.cursorPos = i;
				}
				else
				{
					value.cursorPos = i + 1;
				}
			}
		}

		//十字キーでカーソル移動
		//[←] キー
		if ((0 < value.cursorPos)
			&& (KeyLeft.down() || ((SecondsF{ 0.33 } < KeyLeft.pressedDuration()) && (SecondsF{ 0.06 } < value.leftPressStopwatch))))
		{
			--value.cursorPos;
			value.leftPressStopwatch.restart();
		}
		//[→] キー
		if ((value.cursorPos < value.text.size())
			&& (KeyRight.down() || ((SecondsF{ 0.33 } < KeyRight.pressedDuration()) && (SecondsF{ 0.06 } < value.rightPressStopwatch))))
		{
			++value.cursorPos;
			value.rightPressStopwatch.restart();
		}

		//バックスペースキーで文字消去
		if ((0 < value.cursorPos)
			 && (KeyBackspace.down() || ((SecondsF{ 0.33 } < KeyBackspace.pressedDuration()) && (SecondsF{ 0.03 } < backspaceStopwatch))))
		{
			value.text = deleteCursorPosText();
			--value.cursorPos;
			backspaceStopwatch.restart();
		}

		//カーソル点滅
		showCursor = (value.cursorStopwatch.ms() % 1200 < 600)
			|| (value.leftPressStopwatch.isRunning() && value.leftPressStopwatch < SecondsF(0.5))
			|| (value.rightPressStopwatch.isRunning() && value.rightPressStopwatch < SecondsF(0.5));
	}
	//非アクティブ
	else
	{
		showCursor = false;
	}

	//テキストが何も無ければ0にする
	if (value.text == U"") value.text = U"0";

	//スピンボックスがマウスオーバーされていたらカーソルの形をIに変更
	if (region.mouseOver() && Cursor::PosF().x < pos.x + width - height)
	{
		Cursor::RequestStyle(CursorStyle::IBeam);
	}
}

void SpinBox::draw() const
{
	//入力用のRectF描画
	region.draw((enable ? Palette::White : Palette::Silver));
	//アクティブなら外枠を青に、それ以外なら黒
	if (value.active) region.drawFrame(1, Palette::Dodgerblue);
	else region.drawFrame(1, Palette::Black);
	//数字描画
	font(value.text).draw(region.pos.x, region.pos.y - 5, Palette::Black);
	//カーソル描画
	const double cursorLinePos = font(value.text.substr(0, value.cursorPos)).region().w + pos.x;
	if (showCursor) Line(cursorLinePos, pos.y + 2, cursorLinePos, pos.y + height - 2).draw(2, Palette::Black);
}

