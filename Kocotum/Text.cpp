#include "Text.hpp"

Text::Text(Vec2 pos, World& world, String text)
	:Object{ pos, world, E_ObjectType::Text, U"テキスト" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, text{ text }
{ }


void Text::restart()
{

}


bool Text::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool Text::mouseOver()
{
	return body.mouseOver();
}

void Text::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void Text::handleCollisionX()
{
}

void Text::handleCollisionY()
{
}

void Text::update()
{
}

void Text::draw() const
{
	FontAsset(U"ObjectText")(text).draw(Arg::leftCenter(pos + Vec2{ 0, CHIP_SIZE.y / 2.0 }), Palette::White);
}
