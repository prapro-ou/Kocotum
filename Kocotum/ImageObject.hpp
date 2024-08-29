#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "World.hpp"
#include "Effect.hpp"


/// @brief 画像
struct ImageObject : public Object
{
	/// @brief 本体
	RectF body;
	/// @brief マウス判定用の矩形
	RectF mouseOverBody;
	/// @brief 画像のテクスチャ
	Texture texture;

	ImageObject(Vec2 pos, World& world, String fileName = U"");

	void loadTexture(String fileName);
	void restart() override;
	bool intersectsPlayer() override;
	bool mouseOver() override;
	void setPos(Vec2 pos) override;
	void handleCollisionX() override;
	void handleCollisionY() override;
	void update() override;
	void draw() const override;
};
