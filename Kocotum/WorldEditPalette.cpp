﻿#include "WorldEditPalette.hpp"

WorldEditPalette::WorldEditPalette(Vec2 pos, uint32 width, uint32 height)
	: pos{ pos }
	, body{ RectF{ pos, width, height } }
	, fileName{ TextBox{ pos + Vec2{ 20, 20 }, 350, 20 } }
	, backgroundIndex{ size_t(0) }
	, background{ RadioButtons{ pos + Vec2{ 20, 150 }, { U"草", U"砂", U"雪", U"洞", U"マグマ" }, backgroundIndex}}
{
	// コンストラクタの初期化
}

void WorldEditPalette::update(World& world)
{
	fileName.update();
	background.update();

	// ファイル読み込みボタンの処理
	if (SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 20, 70 }))
	{
		// ファイル選択ダイアログを開く
		Optional<FilePath> path = Dialog::OpenFile({ FileFilter::CSV() });

		if (path.has_value())
		{
			// ワールドを初期化
			world.clear();
			// 選択されたファイルからワールドを読み込む
			world.loadWorld(*path);
			backgroundIndex = world.backgroundIndex;

			fileName.setText(FileSystem::FileName(*path));
		}
	}

	if (SimpleGUI::Button(U"ファイル保存", pos + Vec2{ 250, 70 }))
	{
		world.saveWorld(U"data/map/" + fileName.getText());
	}

	world.backgroundIndex = backgroundIndex;
}

void WorldEditPalette::draw() const
{
	// パレットの背景を描画
	body.draw(Palette::Azure).drawFrame(2, Palette::Dimgray);

	//SimpleGUI::GetFont()(U".csv").draw(Arg::leftCenter(pos + Vec2(375, 40)), Palette::Black);
	fileName.draw();

	// ファイル読み込みボタンを描画(描画するだけ)
	SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 20, 70 });
	SimpleGUI::Button(U"ファイル保存", pos + Vec2{ 250, 70 });

	background.draw();
}
