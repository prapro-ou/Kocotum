﻿#include "GameCamera.hpp"

CameraArea::CameraArea(Vec2 pos, Vec2 initPos, double width, double height, Vec2 velocity, double scale, bool isScroll)
	: pos{ pos }
	, initPos{ initPos }
	, velocity{ velocity }
	, width{ width }
	, height{ height }
	, scale{ scale }
	, isScroll{ isScroll }
	, area{ RectF{ pos, width, height } }
{
	cameraTargetPos = initPos;
}

void CameraArea::setPos(Vec2 pos)
{
	this->pos = pos;
	area.setPos(pos);
}

void CameraArea::setWidth(double width)
{
	this->width = width;
	area.setSize(width, this->height);
}

void CameraArea::setHeight(double height)
{
	this->height = height;
	area.setSize(this->width, height);
}

void CameraArea::restart()
{
	cameraTargetPos = initPos;
}

void CameraArea::update(const Player& player)
{
	if (isScroll)
	{
		if (player.isAlive)
		{
			cameraTargetPos += velocity * Scene::DeltaTime();
		}
	}
	else
	{
		// プレイヤーの位置に基づいてカメラのターゲット位置を更新
		cameraTargetPos = player.pos + Vec2{ player.velocity.x / 5, 0 };
		cameraTargetPos.x = Clamp(cameraTargetPos.x, pos.x + Scene::CenterF().x * (1.0 / scale), pos.x + width - Scene::CenterF().x * (1.0 / scale));
		cameraTargetPos.y = Clamp(cameraTargetPos.y, pos.y + Scene::CenterF().y * (1.0 / scale), pos.y + height - Scene::CenterF().y * (1.0 / scale));
	}
}

void CameraArea::drawArea() const
{
	area.draw(Palette::Plum.withA(100)).drawFrame(5, 0, Palette::Fuchsia);
	Circle{ initPos, 2 }.draw(Palette::Orange);
}

GameCamera::GameCamera()
	: camera{ Camera2D{ Vec2{ 0, 0 }, 1.0, CameraControl::None_ } }
	, activeArea{ std::make_shared<CameraArea>(Vec2{ 0, 0 }, Scene::CenterF()) }
{
	areas.clear();
}

void GameCamera::addArea(std::shared_ptr<CameraArea> area)
{
	areas << area;
}

bool GameCamera::isPlayerOutOfScreen(const Player& player)
{
	RectF cameraTargetArea = RectF{ Arg::center(activeArea->cameraTargetPos), Scene::Size() * (1 / activeArea->scale) };

	return not cameraTargetArea.stretched(CHIP_SIZE * 3).intersects(player.body);
}

void GameCamera::restart()
{
	activeArea->restart();
}

void GameCamera::init()
{
	activeArea->restart();
	camera.setCenter(activeArea->cameraTargetPos);
	camera.setScale(activeArea->scale);
}

void GameCamera::update(const Player& player)
{
	// プレイヤーの位置に基づいてアクティブな領域を更新
	for (auto& area : areas)
	{
		if (player.pos.intersects(area->area))
		{
			activeArea = area;
		}
	}

	activeArea->update(player);

	// カメラの位置とスケールを更新
	camera.setTargetCenter(activeArea->cameraTargetPos);
	camera.setTargetScale(activeArea->scale);
	camera.update();
}

void GameCamera::drawArea() const
{
	for (auto& area : areas)
	{
		area->drawArea();
	}
}

Transformer2D GameCamera::createTransformer() const
{
	return camera.createTransformer();
}
