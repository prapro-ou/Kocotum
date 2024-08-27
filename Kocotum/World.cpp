#include "World.hpp"

World::World(Vec2 pos)
	: player{ Player{ pos } }
	, causeWarp{ false }
	, warpFileName{ U"" }
	, backgroundIndex{ size_t(0) }
{
	
}


void World::clear()
{
	this->objects.clear();
	this->camera.areas.clear();
}

void World::loadWorld(String fileName)
{
	clear();

	const CSV csv{ fileName };
	if (!csv)
	{
		Console << fileName;
		return;
	}

	this->fileName = fileName;

	for (size_t row = 0; row < csv.rows(); ++row)
	{
		if (csv[row][0] == U"Camera")
		{
			// カメラ領域の読み込み
			Vec2 pos = Parse<Vec2>(csv[row][1]);
			Vec2 initPos = Parse<Vec2>(csv[row][4]);
			double width = Parse<double>(csv[row][2]);
			double height = Parse<double>(csv[row][3]);
			double scale = Parse<double>(csv[row][5]);
			bool isScroll = Parse<bool>(csv[row][6]);
			Vec2 velocity = Parse<Vec2>(csv[row][7]);

			camera.addArea(std::make_shared<CameraArea>(pos, initPos, width, height, velocity, scale, isScroll));
		}
		else if (csv[row][0] == U"Object")
		{
			// オブジェクトの読み込み
			if (csv[row][1] == U"Wall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				size_t textureIndex = ParseOr<size_t>(csv[row][3], 1);
				addObject(std::make_shared<Wall>(pos, *this, textureIndex));
				//addObject(std::make_shared<Wall>(pos, *this, 1));
			}
			else if (csv[row][1] == U"JumpToggleWall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				bool init = Parse<bool>(csv[row][3]);
				addObject(std::make_shared<JumpToggleWall>(pos, *this, init));
			}
			else if (csv[row][1] == U"IceWall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				size_t textureIndex = ParseOr<size_t>(csv[row][3], 1);
				addObject(std::make_shared<IceWall>(pos, *this, textureIndex));
				//addObject(std::make_shared<IceWall>(pos, *this, 1));
			}
			else if (csv[row][1] == U"SpeedWall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				addObject(std::make_shared<SpeedWall>(pos, *this));
			}
			else if (csv[row][1] == U"DangerWall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				size_t textureIndex = ParseOr<size_t>(csv[row][3], 1);
				addObject(std::make_shared<DangerWall>(pos, *this, textureIndex));
				//addObject(std::make_shared<DangerWall>(pos, *this, 1));
			}
			else if (csv[row][1] == U"Needle")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				size_t textureIndex = ParseOr<size_t>(csv[row][4], 1);
				addObject(std::make_shared<Needle>(pos, *this, (E_Direction)direction, textureIndex));
				//addObject(std::make_shared<Needle>(pos, *this, (E_Direction)direction, 1));
			}
			else if (csv[row][1] == U"MiniNeedle")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				addObject(std::make_shared<MiniNeedle>(pos, *this, (E_Direction)direction));
			}
			else if (csv[row][1] == U"JumpToggleNeedle")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				bool init = Parse<bool>(csv[row][4]);
				addObject(std::make_shared<JumpToggleNeedle>(pos, *this, init, (E_Direction)direction));
			}
			else if (csv[row][1] == U"GravityLineHorizontal")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				double length = Parse<double>(csv[row][3]);
				addObject(std::make_shared<GravityLineHorizontal>(pos, *this, length));
			}
			else if (csv[row][1] == U"GravityLineVertical")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				double length = Parse<double>(csv[row][3]);
				addObject(std::make_shared<GravityLineVertical>(pos, *this, length));
			}
			else if (csv[row][1] == U"StartPoint")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				addObject(std::make_shared<StartPoint>(pos, *this));
			}
			else if (csv[row][1] == U"SavePoint")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				addObject(std::make_shared<SavePoint>(pos, *this));
			}
			else if (csv[row][1] == U"Text")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				String text = csv[row][3];
				addObject(std::make_shared<Text>(pos, *this, text));
			}
			else if (csv[row][1] == U"WarpPoint")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				String fileName = csv[row][3];
				addObject(std::make_shared<WarpPoint>(pos, *this, fileName));
			}
			else if (csv[row][1] == U"OneWayFloor")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				size_t textureIndex = ParseOr<size_t>(csv[row][3], 1);
				addObject(std::make_shared<OneWayFloor>(pos, *this, textureIndex));
				//addObject(std::make_shared<OneWayFloor>(pos, *this, 1));
			}
			else if (csv[row][1] == U"MoveFloor")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				double length = Parse<double>(csv[row][4]);
				addObject(std::make_shared<MoveFloor>(pos, *this, (E_Direction)direction, length));
			}
			else if (csv[row][1] == U"TouchActiveFloor")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				double length = Parse<double>(csv[row][4]);
				addObject(std::make_shared<TouchActiveFloor>(pos, *this, (E_Direction)direction, length));
			}
			else if (csv[row][1] == U"Spring")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				addObject(std::make_shared<Spring>(pos, *this));
			}
			else if (csv[row][1] == U"TrojanDestroy")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				addObject(std::make_shared<TrojanDestroy>(pos, *this));
			}
		}
		else if (csv[row][0] == U"Background")
		{
			backgroundIndex = Parse<size_t>(csv[row][1]);
		}
	}
}

void World::saveWorld(String fileName)
{
	CSV csv;

	// カメラ領域の保存
	for (const auto& area : camera.areas)
	{
		csv.write(U"Camera");
		csv.write(area->pos.asPoint());
		csv.write(area->width);
		csv.write(area->height);
		csv.write(area->initPos.asPoint());
		csv.write(area->scale);
		csv.write(area->isScroll);
		csv.write(area->velocity.asPoint());
		csv.newLine();
	}

	// オブジェクトの保存
	for (const auto& object : objects)
	{
		csv.write(U"Object");

		if (auto wall = std::dynamic_pointer_cast<Wall>(object))
		{
			csv.write(U"Wall");
			csv.write(wall->pos.asPoint());
			csv.write(wall->textureIndex);
		}
		else if (auto jumpToggleWall = std::dynamic_pointer_cast<JumpToggleWall>(object))
		{
			csv.write(U"JumpToggleWall");
			csv.write(jumpToggleWall->pos.asPoint());
			csv.write(jumpToggleWall->init);
		}
		else if (auto iceWall = std::dynamic_pointer_cast<IceWall>(object))
		{
			csv.write(U"IceWall");
			csv.write(iceWall->pos.asPoint());
			csv.write(iceWall->textureIndex);
		}
		else if (auto speedWall = std::dynamic_pointer_cast<SpeedWall>(object))
		{
			csv.write(U"SpeedWall");
			csv.write(speedWall->pos.asPoint());
		}
		else if (auto dangerWall = std::dynamic_pointer_cast<DangerWall>(object))
		{
			csv.write(U"DangerWall");
			csv.write(dangerWall->pos.asPoint());
			csv.write(dangerWall->textureIndex);
		}
		else if (auto needle = std::dynamic_pointer_cast<Needle>(object))
		{
			csv.write(U"Needle");
			csv.write(needle->pos.asPoint());
			csv.write((uint8)needle->direction);
			csv.write(needle->textureIndex);
		}
		else if (auto miniNeedle = std::dynamic_pointer_cast<MiniNeedle>(object))
		{
			csv.write(U"MiniNeedle");
			csv.write(miniNeedle->pos.asPoint());
			csv.write((uint8)miniNeedle->direction);
		}
		else if (auto jumpToggleNeedle = std::dynamic_pointer_cast<JumpToggleNeedle>(object))
		{
			csv.write(U"JumpToggleNeedle");
			csv.write(jumpToggleNeedle->pos.asPoint());
			csv.write((uint8)jumpToggleNeedle->direction);
			csv.write(jumpToggleNeedle->init);
		}
		else if (auto gravityLineHorizontal = std::dynamic_pointer_cast<GravityLineHorizontal>(object))
		{
			csv.write(U"GravityLineHorizontal");
			csv.write(gravityLineHorizontal->pos.asPoint());
			csv.write(gravityLineHorizontal->length);
		}
		else if (auto gravityLineVertical = std::dynamic_pointer_cast<GravityLineVertical>(object))
		{
			csv.write(U"GravityLineVertical");
			csv.write(gravityLineVertical->pos.asPoint());
			csv.write(gravityLineVertical->length);
		}
		else if (auto startPoint = std::dynamic_pointer_cast<StartPoint>(object))
		{
			csv.write(U"StartPoint");
			csv.write(startPoint->pos.asPoint());
		}
		else if (auto savePoint = std::dynamic_pointer_cast<SavePoint>(object))
		{
			csv.write(U"SavePoint");
			csv.write(savePoint->pos.asPoint());
		}
		else if (auto text = std::dynamic_pointer_cast<Text>(object))
		{
			csv.write(U"Text");
			csv.write(text->pos.asPoint());
			csv.write(text->text);
		}
		else if (auto warpPoint = std::dynamic_pointer_cast<WarpPoint>(object))
		{
			csv.write(U"WarpPoint");
			csv.write(warpPoint->pos.asPoint());
			csv.write(warpPoint->fileName);
		}
		else if (auto oneWayFloor = std::dynamic_pointer_cast<OneWayFloor>(object))
		{
			csv.write(U"OneWayFloor");
			csv.write(oneWayFloor->pos.asPoint());
			csv.write(oneWayFloor->textureIndex);
		}
		else if (auto moveFloor = std::dynamic_pointer_cast<MoveFloor>(object))
		{
			csv.write(U"MoveFloor");
			csv.write(moveFloor->pos.asPoint());
			csv.write((uint16)moveFloor->direction);
			csv.write(moveFloor->length);
		}
		else if (auto touchActiveFloor = std::dynamic_pointer_cast<TouchActiveFloor>(object))
		{
			csv.write(U"TouchActiveFloor");
			csv.write(touchActiveFloor->pos.asPoint());
			csv.write((uint16)touchActiveFloor->direction);
			csv.write(touchActiveFloor->length);
		}
		else if (auto spring = std::dynamic_pointer_cast<Spring>(object))
		{
			csv.write(U"Spring");
			csv.write(spring->pos.asPoint());
		}
		else if (auto trojanDestroy = std::dynamic_pointer_cast<TrojanDestroy>(object))
		{
			csv.write(U"TrojanDestroy");
			csv.write(trojanDestroy->pos.asPoint());
		}

		csv.newLine();
	}

	csv.write(U"Background");
	csv.write(backgroundIndex);

	csv.save(fileName);
}

void World::addObject(std::shared_ptr<Object> object)
{
	objects << object;
}

void World::restart()
{
	for (auto& object : objects)
	{
		object->restart();
	}

	player.restart();

	camera.restart();

	deathSw.reset();
}

void World::init()
{
	for (auto& object : objects)
	{
		object->restart();
		if (auto startPoint = std::dynamic_pointer_cast<StartPoint>(object))
		{
			player.respawnPos = startPoint->pos;
		}
	}

	player.restart();

	camera.update(player);

	camera.init();

	deathSw.reset();
}

void World::warp()
{
	loadWorld(warpFileName);
	init();
	savePlayer(player.respawnPos);


	restart();
	camera.camera.jumpTo(camera.activeArea->cameraTargetPos, camera.activeArea->scale);
}

void World::update()
{
	// オブジェクトの更新
	for (auto& object : objects)
	{
		object->update();
	}

	// プレイヤーの更新
	if (player.isAlive)
	{
		player.update(objects);
	}


	// カメラの更新
	camera.update(player);

	if (camera.activeArea->isScroll and camera.isPlayerOutOfScreen(player))
	{
		killPlayer();
	}

	if (causeWarp)
	{
		causeWarp = false;
		warp();
	}
}

void World::draw() const
{
	effect.update();

	// オブジェクトの描画
	for (auto& object : objects)
	{
		if (auto obj = std::dynamic_pointer_cast<Text>(object))
		{

		}
		else
		{
			object->draw();
		}
	}

	for (auto& object : objects)
	{
		if (auto obj = std::dynamic_pointer_cast<Text>(object))
		{
			object->draw();
		}
	}

	// プレイヤーの描画
	if (player.isAlive)
	{
		player.draw();
	}
}
