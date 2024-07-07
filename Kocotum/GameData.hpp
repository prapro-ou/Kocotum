# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "World.hpp"


struct GameData
{
	World world{ Vec2{ 256, 128 } };
};

using App = SceneManager<String, GameData>;
