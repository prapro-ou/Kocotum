#include "Wall.hpp"

ImageObject::ImageObject(Vec2 pos, World& world, Size size, String fileName)
	: Object{ pos, world, U"画像"}
	, body{ RectF{ pos, size } }
	, fileName{ fileName }
	, texture{ Texture{ fileName } }
{
}

void ImageObject::loadTexture(String fileName)
{
	this->fileName = fileName;
	texture = Texture{ fileName };
}

void ImageObject::restart()
{
}

bool ImageObject::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool ImageObject::mouseOver()
{
	return body.mouseOver();
}

void ImageObject::setPos(Vec2 pos)
{
	this->pos = pos;
	body.setPos(pos);
}

void ImageObject::handleCollisionX()
{
}

void ImageObject::handleCollisionY()
{
}

void ImageObject::update()
{
}

void ImageObject::draw() const
{
	texture.resized(body.size).draw(pos);
}
