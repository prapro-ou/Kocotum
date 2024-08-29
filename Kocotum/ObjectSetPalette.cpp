#include "ObjectSetPalette.hpp"

ObjectSetPalette::ObjectSetPalette(Vec2 pos, uint32 width, uint32 height)
	: pos{ pos }
	, body{ RectF{pos, width, height} }
	, indexDirection{ size_t(0) }
	, indexJumpToggle{ size_t(0) }
	, direction{ RadioButtons{ pos + Vec2{ 120, 100 }, { U"↑", U"→", U"↓", U"←" }, indexDirection } }
	, jumpToggle{ RadioButtons{ pos + Vec2{ 240, 200 }, { U"出現", U"消滅" }, indexJumpToggle } }
	, length{ SpinBox(pos + Vec2{ 120, 300 }, 150, 40, 5, U"64") }
	, text{ TextBox(pos + Vec2{ 120, 350 }, 400, 20, U"Text") }
	, fileName{ U"" }
	, sizeX{ SpinBox(pos + Vec2{ 50, 550 }, 150, 30, 5, U"1") }
	, sizeY{ SpinBox(pos + Vec2{ 250, 550 }, 150, 30, 5, U"1") }
	, texture{ SpinBox{ pos + Vec2{ 2, 650 }, 150, 40, 5, U"1"} }
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
	else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(object))
	{
		indexDirection = (size_t)moveFloor->direction;
	}
	else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(object))
	{
		indexDirection = (size_t)touchActiveFloor->direction;
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
	else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(object))
	{
		length.setValue((int)moveFloor->length / CHIP_SIZE.x);
	}
	else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(object))
	{
		length.setValue((int)touchActiveFloor->length / CHIP_SIZE.x);
	}

	if (auto objectText = std::dynamic_pointer_cast<Text>(object))
	{
		text.setText(objectText->text);
	}

	if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(object))
	{
		fileName = warpPoint->fileName;
	}
	else if (auto imageObject = std::dynamic_pointer_cast<ImageObject>(object))
	{
		fileName = imageObject->fileName;
	}

	if (auto imageObject = std::dynamic_pointer_cast<ImageObject>(object))
	{
		sizeX.setValue(imageObject->body.size.x / CHIP_SIZE.x);
		sizeY.setValue(imageObject->body.size.y / CHIP_SIZE.y);
	}

	if (auto wall = std::dynamic_pointer_cast<Wall>(object))
	{
		texture.setValue((int)(wall->textureIndex));
	}
	else if (auto oneWayFloor = std::dynamic_pointer_cast<OneWayFloor>(object))
	{
		texture.setValue((int)(oneWayFloor->textureIndex));
	}
	else if (auto iceWall = std::dynamic_pointer_cast<IceWall>(object))
	{
		texture.setValue((int)(iceWall->textureIndex));
	}
	else if (auto needle = std::dynamic_pointer_cast<Needle>(object))
	{
		texture.setValue((int)(needle->textureIndex));
	}
	else if (auto dangerWall = std::dynamic_pointer_cast<DangerWall>(object))
	{
		texture.setValue((int)(dangerWall->textureIndex));
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
	else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(object))
	{
		moveFloor->setDirection((E_Direction)indexDirection);
	}
	else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(object))
	{
		touchActiveFloor->setDirection((E_Direction)indexDirection);
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
	else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(object))
	{
		moveFloor->length = length.getValue() * CHIP_SIZE.x;
	}
	else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(object))
	{
		touchActiveFloor->length = length.getValue() * CHIP_SIZE.x;
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
		Optional<FilePath> path = Dialog::OpenFile({ FileFilter::AllFiles() });

		if (path.has_value())
		{
			if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(object))
			{
				warpPoint->fileName = FileSystem::RelativePath(*path);
				fileName = FileSystem::RelativePath(*path);
			}
			else if (auto imageObject = std::dynamic_pointer_cast<ImageObject>(object))
			{
				imageObject->loadTexture(FileSystem::RelativePath(*path));
				fileName = FileSystem::RelativePath(*path);
			}
		}
	}

	sizeX.update();
	sizeY.update();

	if (auto imageObject = std::dynamic_pointer_cast<ImageObject>(object))
	{
		imageObject->body.setSize(Size{ sizeX.getValue(), sizeY.getValue() } *CHIP_SIZE);
	}

	texture.update();
	if (auto wall = std::dynamic_pointer_cast<Wall>(object))
	{
		wall->textureIndex = (size_t)texture.getValue();
	}
	else if (auto oneWayFloor = std::dynamic_pointer_cast<OneWayFloor>(object))
	{
		oneWayFloor->textureIndex = (size_t)texture.getValue();
	}
	else if (auto iceWall = std::dynamic_pointer_cast<IceWall>(object))
	{
		iceWall->textureIndex = (size_t)texture.getValue();
	}
	else if (auto needle = std::dynamic_pointer_cast<Needle>(object))
	{
		needle->textureIndex = (size_t)texture.getValue();
	}
	else if (auto dangerWall = std::dynamic_pointer_cast<DangerWall>(object))
	{
		dangerWall->textureIndex = (size_t)texture.getValue();
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
	SimpleGUI::GetFont()(U"画像サイズ").draw(pos + Vec2{ 20, 520 }, Palette::Black);
	SimpleGUI::GetFont()(U"幅:").draw(pos + Vec2{ 20, 550 }, Palette::Black);
	SimpleGUI::GetFont()(U"高さ:").draw(pos + Vec2{ 200, 550 }, Palette::Black);
	sizeX.draw();
	sizeY.draw();
	SimpleGUI::GetFont()(U"テクスチャ番号").draw(pos + Vec2{ 0, 600 }, Palette::Black);
	texture.draw();
}
