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

		getData().world.trojanForce.update();

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
			getData().world.restart();
			getData().world.update();
		}
	}

	void draw() const override
	{
		//Print << getData().world.player.pos;
		TextureAsset(U"Background" + Format(getData().world.backgroundIndex)).resized(Scene::Size()).draw(Vec2{ 0, 0 });
		{
			const Transformer2D cameraTransformer = getData().world.camera.createTransformer();
			getData().world.draw();
		}

		getData().world.trojanForce.draw();
	}
};
