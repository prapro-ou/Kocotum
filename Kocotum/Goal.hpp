# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "Object.hpp"
# include "Player.hpp"
# include "Objects.hpp"
# include "World.hpp"
# include "GameData.hpp"

class Star {

	//星の数
	int32 starCount;

	//星の大きさ
	double minSize, maxSize;

	//double 星の色
	ColorF starCol;

	//星の生成エリア
	Rect starArea;

	//☆
	Array<Circle> stars;

public:
	Star(Rect _starArea = Scene::Rect(), int32 _starCount = 30)
		:starArea(_starArea), starCount(_starCount), minSize(1.0), maxSize(2.0), starCol(Palette::White)
	{
		//星をランダムに配置
		stars.clear();
		for (int i : step(starCount))stars.push_back(Circle(RandomVec2(starArea), Random(minSize, maxSize)));
	}
	void update() {}
	void draw() const {
		for (const auto& s : stars)s.draw(ColorF{ starCol,Random(0.5,0.85) });
	}
	Star& setStarCount(int32 _starCount) { starCount = _starCount; return *this; }
	Star& setMinSize(double _minSize) { minSize = _minSize; return *this; }
	Star& setMaxSize(double _maxSize) { maxSize = _maxSize; return *this; }
	Star& setStarCol(ColorF _starCol) { starCol = _starCol; return *this; }
	Star& setStarArea(Rect _starArea) { starArea = _starArea; return *this; }
	void create() {
		stars.clear();
		for (int i : step(starCount))stars.push_back(Circle(RandomVec2(starArea), Random(minSize, maxSize)));
	};
};


class Goal : public App::Scene
{
private:
	const Font font{ 80, Typeface::Bold };
	const Font sfont{ 50, Typeface::Bold };
	Star stars;

public:

	Goal(const InitData& init)
		:IScene{ init }
	{
		getData().sw.pause();
		stars.setStarArea(Rect{ 0,0,Scene::Width(),Scene::Height() * 2 / 3 })
			.setStarCol(Palette::Aqua)
			.setStarCount(50);
		stars.create();
	}


	void update() override
	{
		stars.update();

		if (KeyEnter.down())
		{
			getData().deathCount = 0;
			getData().sw.reset();
			getData().world.warpFileName = U"data/map/title.csv";
			getData().world.warp();
			getData().world.restart();
			getData().world.update();
			getData().world.isGoal = false;
			changeScene(U"Play");
		}
	}

	void draw() const override
	{
		Scene::Rect().draw(Arg::top = ColorF(0.0, 0.0, 0.2), Arg::bottom = ColorF(0.2, 0.2, 0.4));
		stars.draw();

		font(U"クリア！").drawAt(Scene::CenterF(), ColorF(1));
		sfont(U"プレイ時間:{:.2f}"_fmt(getData().sw.sF())).drawAt(Scene::CenterF().movedBy(0, 150), ColorF(1));
		sfont(U"リトライ回数:{}"_fmt(getData().deathCount)).drawAt(Scene::CenterF().movedBy(0, 250), ColorF(1));
		sfont(U"Enterで初めからプレイ").drawAt(Scene::CenterF().movedBy(0, 350), ColorF(1));
	}
};
