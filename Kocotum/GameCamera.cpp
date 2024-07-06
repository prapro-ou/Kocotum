#include "GameCamera.hpp"

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

void CameraArea::init()
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
		cameraTargetPos = player.pos + Vec2{ player.velocity.x / 3, 0 };
		cameraTargetPos.x = Clamp(cameraTargetPos.x, pos.x + Scene::CenterF().x * scale, pos.x + width - Scene::CenterF().x * scale);
		cameraTargetPos.y = Clamp(cameraTargetPos.y, pos.y + Scene::CenterF().y * scale, pos.y + height - Scene::CenterF().y * scale);
	}
}

void CameraArea::drawArea() const
{
	area.draw(Palette::Plum.withA(25)).drawFrame(1, 0, Palette::Fuchsia);
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
	// プレイヤーが画面外にいるかどうかのチェック処理を実装する
	return false;
}

void GameCamera::restart()
{
	activeArea->init();
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
