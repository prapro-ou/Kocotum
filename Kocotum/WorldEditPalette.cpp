#include "WorldEditPalette.hpp"

WorldEditPalette::WorldEditPalette(Vec2 pos, uint32 width, uint32 height)
	: pos{ pos }
	, body{ RectF{pos, width, height} }
{
	// コンストラクタの初期化
}

void WorldEditPalette::update(World& world)
{
	// ファイル読み込みボタンの処理
	if (SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 20, 200 }))
	{
		// ファイル選択ダイアログを開く
		Optional<FilePath> path = Dialog::OpenFile({ FileFilter::CSV() });

		if (path.has_value())
		{
			// 選択されたファイルからワールドを読み込む
			world.loadWorld(*path);
		}
	}
}

void WorldEditPalette::draw() const
{
	// パレットの背景を描画
	body.draw(Palette::Azure).drawFrame(2, Palette::Dimgray);

	// ファイル読み込みボタンを描画(描画するだけ)
	SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 20, 200 });
}
