# pragma once
# include <Siv3D.hpp>


const Vec2 CHIP_SIZE = Vec2{ 50, 50 };

enum class E_Object
{
	Wall,
	Needle,
	MiniNeedle,
	GravityLine,
	JumpToggleWall,
	JumpToggleNeedle,
	MoveFloorHorizontal,
	MoveFloorVertical,
};

enum class E_Direction : uint16
{
	Up,
	Right,
	Down,
	Left,
};

struct Player;

/// @brief マップ上に配置されているオブジェクトの基底クラス
struct Object
{
	Vec2 pos;
	Effect& effect;
	Player& player;
	E_Object type;

	Object(Vec2 pos, Effect& effect, Player& player, E_Object type)
		: pos{ pos }
		, effect{ effect }
		, player{ player }
		, type{ type }
	{ }

	virtual void restart() = 0;

	virtual bool intersectsPlayer() = 0;

	virtual bool mouseOver() = 0;

	virtual void handleCollisionX() = 0;

	virtual void handleCollisionY() = 0;

	virtual void update() = 0;

	virtual void draw() const = 0;

private:

};
