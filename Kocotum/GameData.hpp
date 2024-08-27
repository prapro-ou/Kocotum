# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "World.hpp"


struct GameData
{
	World world{ Vec2{ 256, 128 } };
	String fileName = U"test.csv";
	uint16 deathCount = 0;
	Stopwatch sw;
};

using App = SceneManager<String, GameData>;
