#include "CameraSetPalette.hpp"

CameraSetPalette::CameraSetPalette(Vec2 pos, uint32 width, uint32 height)
	: pos{ pos }
	, body{ RectF{pos, width, height} }
	, posX{ SpinBox(pos + Vec2{ 50, 50 }, 150, 30, 5, U"64") }
	, posY{ SpinBox(pos + Vec2{ 250, 50 }, 150, 30, 5, U"64") }
	, width{ SpinBox(pos + Vec2{ 50, 100 }, 150, 30, 5, U"64") }
	, height{ SpinBox(pos + Vec2{ 250, 100 }, 150, 30, 5, U"64") }
	, initX{ SpinBox(pos + Vec2{ 50, 180 }, 150, 30, 5, U"64") }
	, initY{ SpinBox(pos + Vec2{ 250, 180 }, 150, 30, 5, U"64") }
	, scale{ SpinBox(pos + Vec2{ 120, 230 }, 150, 30, 5, U"64") }
	, indexScroll{ size_t(0) }
	, scroll{ RadioButtons{ pos + Vec2{ 120, 300 }, { U"しない", U"する" }, indexScroll} }
	, velocityX{ SpinBox(pos + Vec2{ 50, 380 }, 150, 30, 5, U"64") }
	, velocityY{ SpinBox(pos + Vec2{ 250, 380 }, 150, 30, 5, U"64") }
{
	// コンストラクタの初期化
}

void CameraSetPalette::loadSettings(std::shared_ptr<CameraArea>& area)
{
	// カメラエリアの設定をSpinBoxに反映
	posX.setValue(area->pos.x / CHIP_SIZE.x);
	posY.setValue(area->pos.y / CHIP_SIZE.y);
	width.setValue(area->width / CHIP_SIZE.x);
	height.setValue(area->height / CHIP_SIZE.y);
	initX.setValue(area->initPos.x / CHIP_SIZE.x);
	initY.setValue(area->initPos.y / CHIP_SIZE.y);
	scale.setValue((int)area->scale * 100);
	indexScroll = area->isScroll;
	velocityX.setValue(area->velocity.x / CHIP_SIZE.x);
	velocityY.setValue(area->velocity.y / CHIP_SIZE.y);
}

void CameraSetPalette::update(std::shared_ptr<CameraArea>& area)
{
	// 各SpinBoxの更新
	posX.update();
	posY.update();
	width.update();
	height.update();
	initX.update();
	initY.update();
	scale.update();
	scroll.update();
	velocityX.update();
	velocityY.update();

	// 更新された値をカメラエリアに反映
	area->setPos(Vec2{ posX.getValue() * CHIP_SIZE.x, posY.getValue() * CHIP_SIZE.y });
	area->setWidth(width.getValue() * CHIP_SIZE.x);
	area->setHeight(height.getValue() * CHIP_SIZE.y);
	area->initPos = Vec2{ initX.getValue() * CHIP_SIZE.x, initY.getValue() * CHIP_SIZE.y };
	area->scale = scale.getValue() / 100.0;
	area->isScroll = indexScroll;
	area->velocity = Vec2{ velocityX.getValue() * CHIP_SIZE.x, velocityY.getValue() * CHIP_SIZE.y };
}

void CameraSetPalette::draw() const
{
	// パレットの背景を描画
	body.draw(Palette::Azure).drawFrame(2, Palette::Dimgray);

	// 各設定項目のラベルと入力欄を描画
	SimpleGUI::GetFont()(U"座標").draw(pos + Vec2{ 20, 20 }, Palette::Black);
	SimpleGUI::GetFont()(U"x:").draw(pos + Vec2{ 30, 50 }, Palette::Black);
	SimpleGUI::GetFont()(U"y:").draw(pos + Vec2{ 230, 50 }, Palette::Black);
	posX.draw();
	posY.draw();

	SimpleGUI::GetFont()(U"幅:").draw(pos + Vec2{ 20, 100 }, Palette::Black);
	SimpleGUI::GetFont()(U"高さ:").draw(pos + Vec2{ 200, 100 }, Palette::Black);
	width.draw();
	height.draw();

	SimpleGUI::GetFont()(U"初期座標").draw(pos + Vec2{ 20, 150 }, Palette::Black);
	SimpleGUI::GetFont()(U"x:").draw(pos + Vec2{ 30, 180 }, Palette::Black);
	SimpleGUI::GetFont()(U"y:").draw(pos + Vec2{ 230, 180 }, Palette::Black);
	initX.draw();
	initY.draw();

	SimpleGUI::GetFont()(U"倍率(%)").draw(pos + Vec2{ 20, 230 }, Palette::Black);
	scale.draw();

	SimpleGUI::GetFont()(U"スクロール").draw(pos + Vec2{ 20, 300 }, Palette::Black);
	scroll.draw();

	SimpleGUI::GetFont()(U"スクロール速度").draw(pos + Vec2{ 20, 350 }, Palette::Black);
	SimpleGUI::GetFont()(U"x:").draw(pos + Vec2{ 30, 380 }, Palette::Black);
	SimpleGUI::GetFont()(U"y:").draw(pos + Vec2{ 230, 380 }, Palette::Black);
	velocityX.draw();
	velocityY.draw();
}
