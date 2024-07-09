#include "ScrollBarV.hpp"

double logN(double x, double n)
{
	return logf(x) / logf(n);
}

ScrollBarV::ScrollBarV(Vec2 pos, double width, double height, double min, double max)
{
	this->pos = pos;
	this->min = min;
	this->max = max;
	this->Area = RectF{ pos, width, height };
	this->Box = RectF{ pos, width, height };
	this->grabbed = false;
	this->max = max;
	this->min = min;
	this->now = 0;
}

bool ScrollBarV::isGrabbed()
{
	return this->grabbed;
}

void ScrollBarV::setMax(double max)
{
	this->max = max;
}

void ScrollBarV::setMin(double min)
{
	this->min = min;
}

void ScrollBarV::setNow(double now)
{
	this->now = now;
}

void ScrollBarV::setInfo(double min, double max, double now)
{
	setMin(min);
	setMax(max);
	setNow(now);
}

double ScrollBarV::getNow()
{
	return this->now;
}

void ScrollBarV::update()
{
	// 最大値と最小値の差
	double range = max - min;
	// スクロールバーのつまみの長さ
	Box.setSize(Box.w, Max(Area.h - logN(range, Area.h * 5) * (Area.h - 30), 50.0));
	// スクロールバーの可動域
	double length = Area.h - Box.h;
	// 1ピクセル当たりの増加量
	double step = range / length;


	//バーが掴まれていたら
	if (grabbed)
	{
		//クリックされたままなら値更新
		if (MouseL.pressed())
		{
			now = min + step * (Cursor::PosF().y - pos.y - Box.h / 2.0);
			now = Clamp(now, min, max);
		}
		//離されたらフラグ更新
		else
		{
			grabbed = false;
		}
	}
	//バーが離されていたら
	else
	{
		//マウスが乗っていてクリックしたらフラグ更新
		if (Area.mouseOver() && MouseL.down()) grabbed = true;
	}

	// ボックスの座標更新
	Box.setPos(Box.pos.x, Area.pos.y + (now - min) / range * length);
}

/// @brief スクロールバーを描画します。
void ScrollBarV::draw() const
{
	//Area.rounded(8).draw(Palette::Ghostwhite).drawFrame(1, ColorF(0.5));
	//if ((isMouseOver() && !MouseL.pressed()) || grabbed) Area.rounded(8).draw(ColorF(0.65, 0.65, 0.85, 0.15));
	Box.rounded(8).draw(ColorF(0.35, 0.75));
	if (Box.mouseOver() || grabbed) Box.rounded(8).draw(ColorF(1, 0.15));
}
