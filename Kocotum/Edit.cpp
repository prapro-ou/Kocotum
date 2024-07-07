# include "Edit.hpp"

Edit::Edit(const InitData& init)
	: IScene{ init }
	, camera{ Camera2D{ Scene::Center(), 1.0, CameraControl::Keyboard } }
	, selectObjectType{ E_ObjectType::Wall }
	, putPalette{ ObjectPutPalette{ Vec2{ 850, 120 } } }
	, setPalette{ ObjectSetPalette{ Vec2{ 850, 120 } } }
	, cameraPalette{ CameraSetPalette{ Vec2{ 850, 120 } } }
	, worldPalette{ WorldEditPalette{ Vec2{ 850, 120 } } }
	, selectObject{ std::make_shared<Wall>(Vec2{ 100, 100 }, getData().world.effect, getData().world.player) }
	, selectCamera{ getData().world.camera.activeArea }
	, state{ E_EditState::PlacingObject }
	, editBox{ RectF{ Vec2{ 850, 0 }, 430, 960 } }
{
	// グリッドの初期化
	grid.clear();
	grid.resize(100, 100);

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
}

void Edit::createObject(Vec2 pos)
{
	// 選択されたオブジェクトタイプに応じてオブジェクトを作成
	switch (selectObjectType)
	{
	case E_ObjectType::Wall:
		getData().world.addObject(std::make_shared<Wall>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::Needle:
		getData().world.addObject(std::make_shared<Needle>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::MiniNeedle:
		getData().world.addObject(std::make_shared<MiniNeedle>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::GravityLineHorizontal:
		getData().world.addObject(std::make_shared<GravityLineHorizontal>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::GravityLineVertical:
		getData().world.addObject(std::make_shared<GravityLineVertical>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::JumpToggleWall:
		getData().world.addObject(std::make_shared<JumpToggleWall>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::JumpToggleNeedle:
		getData().world.addObject(std::make_shared<JumpToggleNeedle>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::MoveFloorHorizontal:
		//getData().world.addObject(std::make_shared<MoveFloorHorizontal>(pos, getData().world.effect, getData().world.player));
		break;
	case E_ObjectType::MoveFloorVertical:
		//getData().world.addObject(std::make_shared<MoveFloorVertical>(pos, getData().world.effect, getData().world.player));
		break;
	}
}

void Edit::update()
{
	camera.update();

	updateCurrentState();
	updatePaletteButtons();
	checkSceneTransition();
}

void Edit::updateCurrentState()
{
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

void Edit::updatePlacingObject()
{
	putPalette.update();
	if (const auto result = putPalette.getClickedType())
	{
		selectObjectType = *result;
	}
	if (not editBox.mouseOver())
	{
		placeOrRemoveObjects();
	}
}

void Edit::placeOrRemoveObjects()
{
	const auto t = camera.createTransformer();
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid[y][x].leftClicked())
			{
				createObject(Vec2{ x * CHIP_SIZE.x, y * CHIP_SIZE.y });
			}
		}
	}

	getData().world.objects.remove_if([](std::shared_ptr<Object> n) { return n->mouseOver() and MouseR.down(); });
}

void Edit::updateSettingObject()
{
	setPalette.update(selectObject);
	if (not editBox.mouseOver())
	{
		selectAndUpdateObject();
	}
}

void Edit::selectAndUpdateObject()
{
	const auto t = camera.createTransformer();

	for (auto& object : getData().world.objects)
	{
		if (object->mouseOver() and MouseL.down())
		{
			selectObject = object;
			setPalette.loadSettings(object);
		}
	}

	getData().world.objects.remove_if([](std::shared_ptr<Object> n) { return n->mouseOver() and MouseR.down(); });
}

void Edit::updateSettingCamera()
{
	cameraPalette.update(selectCamera);
	if (not editBox.mouseOver())
	{
		updateCameraAreas();
	}
}

void Edit::updateCameraAreas()
{
	const auto t = camera.createTransformer();

	bool isMouseOverCameraArea = checkMouseOverCameraArea();
	addNewCameraAreaIfNeeded(isMouseOverCameraArea);
	removeCameraAreaIfRequested();
}

bool Edit::checkMouseOverCameraArea()
{
	for (auto& area : getData().world.camera.areas)
	{
		if (area->area.mouseOver())
		{
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

void Edit::addNewCameraAreaIfNeeded(bool isMouseOverCameraArea)
{
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid[y][x].leftClicked() and not isMouseOverCameraArea)
			{
				Vec2 nowPos = Vec2{ x * CHIP_SIZE.x, y * CHIP_SIZE.y };
				getData().world.camera.addArea(std::make_shared<CameraArea>(nowPos, nowPos + Scene::CenterF()));
				selectCamera = getData().world.camera.areas.back();
				cameraPalette.loadSettings(selectCamera);
			}
		}
	}
}

void Edit::removeCameraAreaIfRequested()
{
	getData().world.camera.areas.remove_if([](std::shared_ptr<CameraArea> n) { return n->area.mouseOver() and MouseR.down(); });
}

void Edit::updateSettingWorld()
{
	worldPalette.update(getData().world);

	if (KeyC.down())
	{
		getData().world.saveWorld(U"test.csv");
	}

	if (KeyL.down())
	{
		getData().world.loadWorld(U"test.csv");
	}
}

void Edit::updatePaletteButtons()
{
	for (int i = 0; i < paletteButtons.size(); i++)
	{
		if (paletteButtons[i].leftClicked())
		{
			state = (E_EditState)i;
		}
	}
}

void Edit::checkSceneTransition()
{
	if (KeyEnter.down())
	{
		changeScene(U"Game");
	}
}

void Edit::draw() const
{
	// グリッドの描画
	{
		const auto t = camera.createTransformer();
		for (int y = 0; y < grid.height(); y++)
		{
			for (int x = 0; x < grid.width(); x++)
			{
				grid[y][x].drawFrame(2, Palette::Black);
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
