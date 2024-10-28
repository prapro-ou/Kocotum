# include "Edit.hpp"

/**
 * @brief コンストラクタ: 初期化データを受け取り、各パレットとオブジェクトを初期化
 *
 * @param init 初期化データ
 */
Edit::Edit(const InitData& init)
	: IScene{ init }
	, camera{ Camera2D{ Scene::Center(), 1.0, CameraControl::Keyboard } }
	, selectObjectType{ std::make_shared<Wall>(Vec2{ 100, 100 }, getData().world) }
	, putPalette{ ObjectPutPalette{ Vec2{ 850, 120 } } }
	, setPalette{ ObjectSetPalette{ Vec2{ 850, 120 } } }
	, cameraPalette{ CameraSetPalette{ Vec2{ 850, 120 } } }
	, worldPalette{ WorldEditPalette{ Vec2{ 850, 120 } } }
	, selectObject{ std::make_shared<Wall>(Vec2{ 100, 100 }, getData().world) }
	, state{ E_EditState::PlacingObject }
	, editBox{ RectF{ Vec2{ 850, 0 }, 430, 960 } }
	, textureIndex{ size_t(1) }
	, gridBox{ RectF{ 20, 900, 200, 40 } }
	, gridIndex{ size_t(0) }
	, gridSelect{ RadioButtons{ Vec2{ 20, 900 }, { U"通常", U"四分割" }, gridIndex } }
	, gridNum{ 1 }
{
	// グリッドの初期化
	grid.clear();
	grid.resize(500, 500);

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			grid[y][x] = RectF{ x * CHIP_SIZE.x, y * CHIP_SIZE.y, CHIP_SIZE };
		}
	}

	// パレットボタンの初期化
	paletteButtons.clear();
	for (int i = 0; i < 4; i++)
	{
		paletteButtons << RectF{ Vec2{ 850 + 107 * i, 20}, 105, 102 };
	}

	// ワールドパレットのファイル名を設定
	worldPalette.fileName.setText(getData().fileName);
	worldPalette.backgroundIndex = getData().world.backgroundIndex;

	if (getData().world.camera.areas.isEmpty())
	{
		selectCamera = getData().world.camera.activeArea;
	}
	else
	{
		selectCamera = getData().world.camera.areas[0];
		cameraPalette.loadSettings(selectCamera);
	}
}

/**
 * @brief オブジェクトを作成する関数
 *
 * @param pos 作成するオブジェクトの位置
 */
void Edit::createObject(Vec2 pos)
{
	// 選択されたオブジェクトタイプに応じてオブジェクトを作成
	if (auto wall = std::dynamic_pointer_cast<Wall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<Wall>(pos, getData().world, textureIndex));
	}
	else if (auto quarterWall = std::dynamic_pointer_cast<QuarterWall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<QuarterWall>(pos, getData().world, textureIndex));
	}
	else if (auto jumpToggleWall = std::dynamic_pointer_cast<JumpToggleWall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<JumpToggleWall>(pos, getData().world));
	}
	else if (auto iceWall = std::dynamic_pointer_cast<IceWall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<IceWall>(pos, getData().world, textureIndex));
	}
	else if (auto speedWall = std::dynamic_pointer_cast<SpeedWall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<SpeedWall>(pos, getData().world));
	}
	else if (auto dangerWall = std::dynamic_pointer_cast<DangerWall>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<DangerWall>(pos, getData().world, textureIndex));
	}
	else if (auto needle = std::dynamic_pointer_cast<Needle>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<Needle>(pos, getData().world, E_Direction::Up, textureIndex));
	}
	else if (auto quarterNeedle = std::dynamic_pointer_cast<QuarterNeedle>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<QuarterNeedle>(pos, getData().world));
	}
	else if (auto miniNeedle = std::dynamic_pointer_cast<MiniNeedle>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<MiniNeedle>(pos, getData().world));
	}
	else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<JumpToggleNeedle>(pos, getData().world));
	}
	else if (auto gravityLineHorizontal = std::dynamic_pointer_cast<GravityLineHorizontal>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<GravityLineHorizontal>(pos, getData().world));
	}
	else if (auto gravityLineVertical = std::dynamic_pointer_cast<GravityLineVertical>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<GravityLineVertical>(pos, getData().world));
	}
	else if (auto startPoint = std::dynamic_pointer_cast<StartPoint>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<StartPoint>(pos, getData().world));
	}
	else if (auto savePoint = std::dynamic_pointer_cast<SavePoint>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<SavePoint>(pos, getData().world));
	}
	else if (auto goalPoint = std::dynamic_pointer_cast<GoalPoint>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<GoalPoint>(pos, getData().world));
	}
	else if (auto text = std::dynamic_pointer_cast<Text>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<Text>(pos, getData().world));
	}
	else if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<WarpPoint>(pos, getData().world));
	}
	else if (auto oneWayFloor = std::dynamic_pointer_cast<OneWayFloor>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<OneWayFloor>(pos, getData().world, textureIndex));
	}
	else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<MoveFloor>(pos, getData().world));
	}
	else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<TouchActiveFloor>(pos, getData().world));
	}
	else if (auto spring = std::dynamic_pointer_cast<Spring>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<Spring>(pos, getData().world));
	}
	else if (auto jumpItem = std::dynamic_pointer_cast<JumpItem>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<JumpItem>(pos, getData().world));
	}
	else if (auto imageObject = std::dynamic_pointer_cast<ImageObject>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<ImageObject>(pos, getData().world));
	}
	else if (auto shrinkItem = std::dynamic_pointer_cast<ShrinkItem>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<ShrinkItem>(pos, getData().world));
	}
	else if (auto growItem = std::dynamic_pointer_cast<GrowItem>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<GrowItem>(pos, getData().world));
	}
	else if (auto neutralizeItem = std::dynamic_pointer_cast<NeutralizeItem>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<NeutralizeItem>(pos, getData().world));
	}
	else if (auto trojanDestroy = std::dynamic_pointer_cast<TrojanDestroy>(selectObjectType))
	{
		getData().world.addObject(std::make_shared<TrojanDestroy>(pos, getData().world));
	}
}

/**
 * @brief 更新関数: カメラや現在の状態を更新
 */
void Edit::update()
{
	// カメラの更新
	camera.update();

	// 現在の状態に応じた更新処理
	updateCurrentState();
	// パレットボタンの更新
	updatePaletteButtons();
	// シーン遷移のチェック
	checkSceneTransition();

	gridSelect.update();
	gridNum = (int8)gridIndex + 1;
}

/**
 * @brief 現在の状態に応じて更新処理を行う
 */
void Edit::updateCurrentState()
{
	// 現在の編集状態に応じた処理を呼び出す
	switch (state)
	{
	case E_EditState::PlacingObject:
		updatePlacingObject();
		break;
	case E_EditState::SettingObject:
		updateSettingObject();
		break;
	case E_EditState::SettingCamera:
		updateSettingCamera();
		break;
	case E_EditState::SettingWorld:
		updateSettingWorld();
		break;
	}
}

/**
 * @brief オブジェクトを配置する状態の更新処理
 */
void Edit::updatePlacingObject()
{
	// オブジェクト配置パレットの更新
	putPalette.update();
	if (const auto result = putPalette.getClickedType())
	{
		// パレットで選択されたオブジェクトタイプを設定
		selectObjectType = *result;
	}
	if (not editBox.mouseOver() and not gridBox.mouseOver())
	{
		// オブジェクトを配置または削除
		placeOrRemoveObjects();
	}
}

/**
 * @brief オブジェクトを配置または削除する処理
 */
void Edit::placeOrRemoveObjects()
{
	const auto t = camera.createTransformer();

	bool isMouseOverObject = false;

	// オブジェクトにマウスオーバーしているか確認
	for (auto& object : getData().world.objects)
	{
		if (object->mouseOver())
		{
			isMouseOverObject = true;
		}
	}

	// グリッド上の各セルをチェック
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			grid[y][x].setSize(CHIP_SIZE / gridNum);
			grid[y][x].setPos(x * CHIP_SIZE.x / gridNum, y * CHIP_SIZE.y / gridNum);
			// マウス左ボタンが押されていて、オブジェクトにマウスオーバーしていない場合
			if (grid[y][x].leftPressed() and not isMouseOverObject)
			{
				// 新しいオブジェクトを作成
				createObject(Vec2{ x * CHIP_SIZE.x / gridNum, y * CHIP_SIZE.y / gridNum });
			}
		}
	}

	// マウス右ボタンが押された場合、オブジェクトを削除
	getData().world.objects.remove_if([](std::shared_ptr<Object> n) { return n->mouseOver() and MouseR.pressed(); });
}

/**
 * @brief オブジェクトを設定する状態の更新処理
 */
void Edit::updateSettingObject()
{
	// オブジェクト設定パレットの更新
	setPalette.update(selectObject);
	if (not editBox.mouseOver())
	{
		// オブジェクトの選択と設定の更新
		selectAndUpdateObject();
	}
}

/**
 * @brief オブジェクトを選択して設定を更新する処理
 */
void Edit::selectAndUpdateObject()
{
	const auto t = camera.createTransformer();

	// オブジェクトにマウスオーバーしていて左クリックされた場合
	for (auto& object : getData().world.objects)
	{
		if (object->mouseOver() and MouseL.down())
		{
			// オブジェクトを選択して設定をロード
			selectObject = object;
			setPalette.loadSettings(object);
		}
	}

	textureIndex = (size_t)setPalette.texture.getValue();

	// マウス右ボタンが押された場合、オブジェクトを削除
	getData().world.objects.remove_if([](std::shared_ptr<Object> n) { return n->mouseOver() and MouseR.pressed(); });
}

/**
 * @brief カメラを設定する状態の更新処理
 */
void Edit::updateSettingCamera()
{
	// カメラ設定パレットの更新
	cameraPalette.update(selectCamera);

	if (not editBox.mouseOver())
	{
		// カメラエリアの更新
		updateCameraAreas();
	}
}

/**
 * @brief カメラエリアを更新する処理
 */
void Edit::updateCameraAreas()
{
	const auto t = camera.createTransformer();

	// カメラエリアにマウスオーバーしているか確認
	bool isMouseOverCameraArea = checkMouseOverCameraArea();
	// 必要に応じて新しいカメラエリアを追加
	addNewCameraAreaIfNeeded(isMouseOverCameraArea);
	// カメラエリアの削除リクエストがある場合に削除
	removeCameraAreaIfRequested();
}

/**
 * @brief マウスオーバーしているカメラエリアをチェックする
 *
 * @return true マウスオーバーしているカメラエリアがある場合
 * @return false マウスオーバーしているカメラエリアがない場合
 */
bool Edit::checkMouseOverCameraArea()
{
	// カメラエリアにマウスオーバーしているか確認
	for (auto& area : getData().world.camera.areas)
	{
		if (area->area.mouseOver())
		{
			// 左クリックされた場合、カメラエリアを選択して設定をロード
			if (MouseL.down())
			{
				selectCamera = area;
				cameraPalette.loadSettings(selectCamera);
			}
			return true;
		}
	}
	return false;
}

/**
 * @brief 必要に応じて新しいカメラエリアを追加する
 *
 * @param isMouseOverCameraArea マウスオーバーしているカメラエリアがあるかどうか
 */
void Edit::addNewCameraAreaIfNeeded(bool isMouseOverCameraArea)
{
	// グリッド上の各セルをチェック
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			// 左クリックされた場合、新しいカメラエリアを追加
			if (grid[y][x].leftClicked() and not isMouseOverCameraArea)
			{
				Vec2 nowPos = Vec2{ x * CHIP_SIZE.x / gridNum, y * CHIP_SIZE.y / gridNum };
				getData().world.camera.addArea(std::make_shared<CameraArea>(nowPos, nowPos + Scene::CenterF()));
				selectCamera = getData().world.camera.areas.back();
				cameraPalette.loadSettings(selectCamera);
			}
		}
	}
}

/**
 * @brief カメラエリアを削除するリクエストがある場合に削除する
 */
void Edit::removeCameraAreaIfRequested()
{
	// マウス右ボタンが押された場合、カメラエリアを削除
	getData().world.camera.areas.remove_if([](std::shared_ptr<CameraArea> n) { return n->area.mouseOver() and MouseR.down(); });
}

/**
 * @brief ワールドを設定する状態の更新処理
 */
void Edit::updateSettingWorld()
{
	// ワールド設定パレットの更新
	worldPalette.update(getData().world);
	// ファイル名の更新
	getData().fileName = worldPalette.fileName.getText();
}

/**
 * @brief パレットボタンの更新処理
 */
void Edit::updatePaletteButtons()
{
	// 各パレットボタンが左クリックされた場合、対応する状態に変更
	for (int i = 0; i < paletteButtons.size(); i++)
	{
		if (paletteButtons[i].leftClicked())
		{
			state = (E_EditState)i;
		}
	}
}

/**
 * @brief シーン遷移をチェックする
 */
void Edit::checkSceneTransition()
{
	// Ctrlキーが押された場合、ゲームシーンに遷移
	if (KeyControl.down())
	{
		changeScene(U"Game");
	}
}

/**
 * @brief 描画関数
 */
void Edit::draw() const
{
	double bright;
	if (getData().world.backgroundIndex == 0)
	{
		bright = 1;
	}
	else
	{
		bright = 0.75;
	}

	TextureAsset(U"Background" + Format(getData().world.backgroundIndex)).resized(Scene::Size()).draw(Vec2{ 0, 0 }, ColorF(bright));

	// グリッドの描画
	{
		const auto t = camera.createTransformer();

		for (size_t i = 0; i <= grid.width(); ++i)
		{
			RectF{ -1, (-1 + (i * CHIP_SIZE.y / gridNum)), (grid.width() * CHIP_SIZE.y / gridNum + 2), 2 }.draw((i % 2 == 0 ? Palette::Magenta : Palette::Black));
			RectF{ (-1 + (i * CHIP_SIZE.x / gridNum)), -1, 2, (grid.height() * CHIP_SIZE.x / gridNum + 2) }.draw((i % 2 == 0 ? Palette::Magenta : Palette::Black));
		}

		for (int y = 0; y < grid.height(); y++)
		{
			for (int x = 0; x < grid.width(); x++)
			{
				if (grid[y][x].mouseOver())
				{
					grid[y][x].draw(ColorF(1, 1, 0, 0.25));
				}
			}
		}

		// カメラエリアとワールドの描画
		getData().world.camera.drawArea();
		getData().world.draw();
	}

	gridBox.draw();
	gridSelect.draw();

	// パレットボタンの描画
	for (int i = 0; i < paletteButtons.size(); i++)
	{
		paletteButtons[i].rounded(5).drawFrame(3, Palette::Dimgray).draw((i == (uint16)state ? Palette::Lightblue : Palette::Whitesmoke));
	}

	// 現在の編集状態に応じたパレットの描画
	switch (state)
	{
	case E_EditState::PlacingObject:
		putPalette.draw();
		break;
	case E_EditState::SettingObject:
		setPalette.draw();
		break;
	case E_EditState::SettingCamera:
		cameraPalette.draw();
		break;
	case E_EditState::SettingWorld:
		worldPalette.draw();
		break;
	}
}
