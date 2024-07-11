#include "ObjectSetPalette.hpp"

ObjectSetPalette::ObjectSetPalette(Vec2 pos, uint32 width, uint32 height)
	: pos{ pos }
	, body{ RectF{pos, width, height} }
	, indexDirection{ size_t(0) }
	, indexJumpToggle{ size_t(0) }
	, direction{ RadioButtons{ pos + Vec2{ 120, 100 }, { U"上", U"右", U"下", U"左" }, indexDirection} }
	, jumpToggle{ RadioButtons{ pos + Vec2{ 240, 200 }, { U"出現", U"消滅" }, indexJumpToggle } }
	, length{ SpinBox(pos + Vec2{ 120, 300 }, 150, 40, 5, U"64") }
	, text{ TextBox(pos + Vec2{ 120, 350 }, 400, 20, U"Text") }
	, fileName{ U"" }
{
	// コンストラクタの初期化
}

void ObjectSetPalette::loadSettings(std::shared_ptr<Object>& object)
{
	// 針オブジェクトの設定を読み込む
	if (auto needle = std::dynamic_pointer_cast<Needle>(object))
	{
		indexDirection = (size_t)needle->direction;
	}
	else if (auto miniNeedle = std::dynamic_pointer_cast<MiniNeedle>(object))
	{
		indexDirection = (size_t)miniNeedle->direction;
	}
	else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(object))
	{
		indexDirection = (size_t)jumpToggleNeedle->direction;
	}

	// ジャンプ切り替えオブジェクトの設定を読み込む
	if (auto jumpToggleWall = std::dynamic_pointer_cast<JumpToggleWall>(object))
	{
		indexJumpToggle = not jumpToggleWall->init;
	}
	else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(object))
	{
		indexJumpToggle = not jumpToggleNeedle->init;
	}


	// 長さを持つオブジェクトの設定を読み込む
	if (auto gravityLineHorizontal = std::dynamic_pointer_cast<GravityLineHorizontal>(object))
	{
		length.setValue((int)gravityLineHorizontal->length / CHIP_SIZE.x);
	}
	else if (auto gravityLineVertical = std::dynamic_pointer_cast<GravityLineVertical>(object))
	{
		length.setValue((int)gravityLineVertical->length / CHIP_SIZE.y);
	}

	if (auto objectText = std::dynamic_pointer_cast<Text>(object))
	{
		text.setText(objectText->text);
	}

	if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(object))
	{
		fileName = warpPoint->fileName;
	}
}

void ObjectSetPalette::update(std::shared_ptr<Object>& object)
{
	// 針オブジェクトの更新
	direction.setEnable(true);
	direction.update();

	if (auto needle = std::dynamic_pointer_cast<Needle>(object))
	{
		needle->setDirection((E_Direction)indexDirection);
	}
	else if (auto miniNeedle = std::dynamic_pointer_cast<MiniNeedle>(object))
	{
		miniNeedle->setDirection((E_Direction)indexDirection);
	}
	else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(object))
	{
		jumpToggleNeedle->setDirection((E_Direction)indexDirection);
	}


	// ジャンプ切り替えオブジェクトの更新
	jumpToggle.setEnable(true);
	jumpToggle.update();

	if (auto jumpToggleWall = std::dynamic_pointer_cast<JumpToggleWall>(object))
	{
		jumpToggleWall->setInit(not (bool)indexJumpToggle);
	}
	else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(object))
	{
		jumpToggleNeedle->setInit(not (bool)indexJumpToggle);
	}


	// 長さを持つオブジェクトの更新
	length.setEnable(true);
	length.update();

	if (auto gravityLineHorizontal = std::dynamic_pointer_cast<GravityLineHorizontal>(object))
	{
		gravityLineHorizontal->length = length.getValue() * CHIP_SIZE.x;
		gravityLineHorizontal->update();
	}
	else if (auto gravityLineVertical = std::dynamic_pointer_cast<GravityLineVertical>(object))
	{
		gravityLineVertical->length = length.getValue() * CHIP_SIZE.y;
		gravityLineVertical->update();
	}

	text.update();

	if (auto objectText = std::dynamic_pointer_cast<Text>(object))
	{
		objectText->text = text.getText();
		objectText->update();
	}

	if (SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 50, 400 }))
	{
		// ファイル選択ダイアログを開く
		Optional<FilePath> path = Dialog::OpenFile({ FileFilter::CSV() });

		if (path.has_value())
		{
			if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(object))
			{
				warpPoint->fileName = FileSystem::FileName(*path);
				fileName = FileSystem::FileName(*path);
			}
		}
	}
}

void ObjectSetPalette::draw() const
{
	// パレットの背景を描画
	body.draw(Palette::Azure).drawFrame(2, Palette::Dimgray);

	// 各設定項目のラベルと入力欄を描画
	SimpleGUI::GetFont()(U"針の向き").draw(pos + Vec2{ 0, 100 }, Palette::Black);
	direction.draw();
	SimpleGUI::GetFont()(U"ジャンプ切り替え初期値").draw(pos + Vec2{ 0, 200 }, Palette::Black);
	jumpToggle.draw();
	SimpleGUI::GetFont()(U"長さ").draw(pos + Vec2{ 0, 300 }, Palette::Black);
	length.draw();
	SimpleGUI::GetFont()(U"テキスト").draw(pos + Vec2{ 0, 350 }, Palette::Black);
	text.draw();
	SimpleGUI::Button(U"ファイル読み込み", pos + Vec2{ 50, 400 });
	SimpleGUI::GetFont()(U"ファイル:" + fileName).draw(pos + Vec2{ 0, 450 }, Palette::Black);
}
