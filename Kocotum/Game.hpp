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
		getData().world.restart();
	}


	void update() override
	{
		getData().world.update();

		if (KeyEnter.down())
		{
			changeScene(U"Edit");
		}
	}

	void draw() const override
	{
		{
			const Transformer2D cameraTransformer = getData().world.camera.createTransformer();
			getData().world.draw();
		}
	}
};
