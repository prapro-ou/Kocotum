﻿# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "Object.hpp"
# include "Player.hpp"
# include "Objects.hpp"
# include "World.hpp"
# include "GameData.hpp"

class Game : public App::Scene
{
public:

	Game(const InitData& init)
		:IScene{ init }
	{
		getData().world.init();
		getData().world.camera.camera.setCenter(getData().world.camera.activeArea->cameraTargetPos);
	}


	void update() override
	{
		getData().world.update();

		if (MouseM.down())
		{
			getData().world.pieMenu = std::make_unique<PieMenu>(getData().world.icons, Scene::CenterF());
			getData().world.pieMenu->setEnabled((size_t)TrojanIndex::Destroy, getData().world.trojanEnable[(size_t)TrojanIndex::Destroy])
				.setEnabled((size_t)TrojanIndex::Transparent, getData().world.trojanEnable[(size_t)TrojanIndex::Transparent])
				.setEnabled((size_t)TrojanIndex::Small, getData().world.trojanEnable[(size_t)TrojanIndex::Small])
				.setEnabled((size_t)TrojanIndex::JumpPlus, getData().world.trojanEnable[(size_t)TrojanIndex::JumpPlus]);
		}

		if (getData().world.pieMenu)
		{
			const Optional<int32> selected = getData().world.pieMenu->update();

			if (MouseM.up())
			{
				if (selected)
				{
					getData().world.trojanIndex.value() = (TrojanIndex)*selected;
				}
				getData().world.pieMenu.reset();
			}
		}

		if (KeyR.down() and getData().world.player.isAlive)
		{
			getData().world.killPlayer();
		}

		if (getData().world.deathSw.sF() > 0.75)
		{
			getData().world.restart();
		}

		if (KeyEnter.down())
		{
			changeScene(U"Edit");
		}
	}

	void draw() const override
	{
		//Print << getData().world.player.pos;
		{
			const Transformer2D cameraTransformer = getData().world.camera.createTransformer();
			getData().world.draw();
		}

		if (getData().world.pieMenu)
		{
			getData().world.pieMenu->draw();
		}
	}
};
