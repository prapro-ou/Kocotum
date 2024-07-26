# pragma once
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

		if (KeyL.down())
		{
			getData().world.pieMenu = std::make_unique<PieMenu>(getData().world.icons, Scene::CenterF());
		}

		if (getData().world.pieMenu)
		{
			if (KeyL.up())
			{
				getData().world.pieMenu.reset();
			}
		}

		if (KeyR.down() or getData().world.deathSw.sF() > 0.75)
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

		}
	}
};
