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
private:
	const Font font{ 80, Typeface::Bold };
	const Font sfont{ 50, Typeface::Bold };

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
			getData().deathCount = 0;
			getData().sw.reset();
			getData().world.warpFileName = U"data/map/title.csv";
			getData().world.warp();
			getData().world.restart();
			getData().world.update();
			changeScene(U"Play");
		}
	}

	void draw() const override
	{
		font(U"クリア！").drawAt(Scene::CenterF());
		sfont(U"プレイ時間:{:.2f}"_fmt(getData().sw.sF())).drawAt(Scene::CenterF().movedBy(0, 150));
		sfont(U"リトライ回数:{}"_fmt(getData().deathCount)).drawAt(Scene::CenterF().movedBy(0, 250));
		sfont(U"Enterで初めからプレイ").drawAt(Scene::CenterF().movedBy(0, 350));
	}
};
