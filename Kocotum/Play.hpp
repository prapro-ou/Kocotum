# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "Object.hpp"
# include "Player.hpp"
# include "Objects.hpp"
# include "World.hpp"
# include "GameData.hpp"

class Play : public App::Scene
{
public:

	Play(const InitData& init)
		:IScene{ init }
	{
		CSV csv{ U"data/save/save.csv" };

		if (not csv)
		{
			getData().world.loadWorld(U"data/map/title.csv");
			getData().world.init();

			getData().world.sw.start();

			csv.write(U"data/map/title.csv");
			csv.newLine();
			csv.write(getData().world.player.pos);
			csv.save(U"data/save/save.csv");
			csv.newLine();
			csv.save(0);
			csv.newLine();
			csv.save(0);
			csv.newLine();
			csv.save(U"data/save/save.csv");

			getData().world.init();
			getData().world.camera.camera.jumpTo(getData().world.camera.activeArea->cameraTargetPos, getData().world.camera.activeArea->scale);
		}
		else
		{
			getData().world.loadWorld(csv[0][0]);
			getData().world.player.respawnPos = Parse<Vec2>(csv[1][0]);
			getData().world.deathCount = Parse<uint16>(csv[2][0]);
			double elapsed = Parse<double>(csv[3][0]);
			getData().world.sw.set((SecondsF)(elapsed));
			getData().world.sw.start();

			getData().world.init();
			getData().world.player.respawnPos = Parse<Vec2>(csv[1][0]);
			getData().world.restart();
			getData().world.camera.camera.jumpTo(getData().world.camera.activeArea->cameraTargetPos, getData().world.camera.activeArea->scale);
		}
	}


	void update() override
	{
		getData().world.update();

		//getData().world.trojanForce.update();

		if (KeyR.down() and getData().world.player.isAlive)
		{
			getData().world.killPlayer();
		}

		if (getData().world.deathSw.sF() > 0.75)
		{
			getData().world.restart();
		}
	}

	void draw() const override
	{
		TextureAsset(U"Background" + Format(getData().world.backgroundIndex)).resized(Scene::Size()).draw(Vec2{ 0, 0 });
		{
			const Transformer2D cameraTransformer = getData().world.camera.createTransformer();
			getData().world.draw();
		}

		//getData().world.trojanForce.draw();
	}
};
