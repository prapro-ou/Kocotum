#include "GoalPoint.hpp"

GoalPoint::GoalPoint(Vec2 pos, World& world)
	:Object{ pos, world, U"ゴール" }
	, body{ RectF{ pos, CHIP_SIZE } }
	, isTouched{ false }
	, gif{ AnimatedGIFReader{ U"data/img/object/WarpPoint.gif" } }
{
	gif.read(images, delays);
	for (const auto& image : images)
	{
		textures << Texture{ image };
	}
	images.clear();
}


void GoalPoint::restart()
{

}


bool GoalPoint::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool GoalPoint::mouseOver()
{
	return body.mouseOver();
}

void GoalPoint::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void GoalPoint::handleCollisionX()
{
	if (not isTouched)
	{
		world.isGoal = true;
		isTouched = true;
	}
}

void GoalPoint::handleCollisionY()
{
	if (not isTouched)
	{
		world.isGoal = true;
		isTouched = true;
	}
}

void GoalPoint::update()
{
	if (not intersectsPlayer())
	{
		isTouched = false;
	}
}

void GoalPoint::draw() const
{
	const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(Scene::Time(), delays);
	if (textures) textures[frameIndex].resized(CHIP_SIZE).draw(pos);
}
