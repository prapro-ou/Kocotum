# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "Object.hpp"
# include "Player.hpp"
# include "Objects.hpp"
# include "World.hpp"
# include "GameData.hpp"

class Goal : public App::Scene
{
public:

	Goal(const InitData& init)
		:IScene{ init }
	{
		getData().sw.pause();
	}


	void update() override
	{
		if (KeyEnter.down())
		{
			changeScene(U"Edit");
			getData().world.restart();
			getData().world.update();
		}
	}

	void draw() const override
	{

	}
};
