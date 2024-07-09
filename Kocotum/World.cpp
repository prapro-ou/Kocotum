#include "World.hpp"

World::World(Vec2 pos)
	: player{ Player{ pos } }
{ }


void World::clear()
{
	this->objects.clear();
	this->camera.areas.clear();

}

void World::loadWorld(String fileName)
{
	const CSV csv{ fileName };
	if (!csv)
	{
		return;
	}

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
				addObject(std::make_shared<Wall>(pos, *this));
			}
			else if (csv[row][1] == U"JumpToggleWall")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				bool init = Parse<bool>(csv[row][3]);
				addObject(std::make_shared<JumpToggleWall>(pos, *this, init));
			}
			else if (csv[row][1] == U"Needle")
			{
				Vec2 pos = Parse<Vec2>(csv[row][2]);
				uint16 direction = Parse<uint16>(csv[row][3]);
				addObject(std::make_shared<Needle>(pos, *this, (E_Direction)direction));
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
		}
		else if (auto jumpToggleWall = std::dynamic_pointer_cast<JumpToggleWall>(object))
		{
			csv.write(U"JumpToggleWall");
			csv.write(jumpToggleWall->pos.asPoint());
			csv.write(jumpToggleWall->init);
		}
		else if (auto needle = std::dynamic_pointer_cast<Needle>(object))
		{
			csv.write(U"Needle");
			csv.write(needle->pos.asPoint());
			csv.write((uint8)needle->direction);
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

		csv.newLine();
	}

	csv.save(fileName);
}

void World::addObject(std::shared_ptr<Object> object)
{
	objects << object;
}

void World::restart()
{
	player.restart();

	for (auto& object : objects)
	{
		object->restart();
	}

	camera.restart();

	deathSw.reset();
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
}

void World::draw() const
{
	effect.update();

	// オブジェクトの描画
	for (auto& object : objects)
	{
		object->draw();
	}

	// プレイヤーの描画
	if (player.isAlive)
	{
		player.draw();
	}
}
