#include "Needle.hpp"

Needle::Needle(Vec2 pos, World& world, E_Direction direction)
	: Object{ pos, world, E_ObjectType::Needle, U"針" }
	, direction{ direction }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ Triangle{ Vec2{ 0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x / 2, 0 }, Vec2{ CHIP_SIZE } } }
{
	body.moveBy(pos);
	body = body.rotatedAt(pos + CHIP_SIZE / 2, (uint8)direction * 90_deg);
}

void Needle::setDirection(E_Direction direction)
{
	// 回転角度を計算し、針の向きと形状を更新
	int8 rotate = (uint8)direction - (uint8)this->direction;
	this->direction = direction;
	body = body.rotatedAt(pos + CHIP_SIZE / 2, rotate * 90_deg);
}

void Needle::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool Needle::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool Needle::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void Needle::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	body.moveBy(this->pos - pos);
	this->pos = pos;
}

void Needle::handleCollisionX()
{
	if (world.player.isAlive)
	{
		// プレイヤーが生きている場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void Needle::handleCollisionY()
{
	if (world.player.isAlive)
	{
		// プレイヤーが生きている場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void Needle::update()
{
	// 更新処理（現在は何もしない）
}

void Needle::draw() const
{
	// 針のテクスチャを描画
	TextureAsset(U"Needle").resized(CHIP_SIZE).rotated((uint8)direction * 90_deg).draw(pos);
}


MiniNeedle::MiniNeedle(Vec2 pos, World& world, E_Direction direction)
	: Object{ pos, world, E_ObjectType::MiniNeedle, U"小さい針" }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, direction{ direction }
{
	// 4つの小さな三角形を作成
	body << Triangle{ Vec2{ 0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x / 8.0, CHIP_SIZE.y * 3.0 / 4.0 }, Vec2{ CHIP_SIZE.x / 4.0, CHIP_SIZE.y } };
	body << Triangle{ Vec2{ CHIP_SIZE.x / 4.0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x * 3.0 / 8.0, CHIP_SIZE.y * 3.0 / 4.0 }, Vec2{ CHIP_SIZE.x / 2.0, CHIP_SIZE.y } };
	body << Triangle{ Vec2{ CHIP_SIZE.x / 2.0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x * 5.0 / 8.0, CHIP_SIZE.y * 3.0 / 4.0 }, Vec2{ CHIP_SIZE.x * 3 / 4.0, CHIP_SIZE.y } };
	body << Triangle{ Vec2{ CHIP_SIZE.x * 3.0 / 4.0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x * 7.0 / 8.0, CHIP_SIZE.y * 3.0 / 4.0 }, Vec2{ CHIP_SIZE } };

	for (auto& b : body)
	{
		b.moveBy(pos);
		b = b.rotatedAt(pos + CHIP_SIZE / 2.0, (uint16)direction * 90_deg);
	}
}

void MiniNeedle::setDirection(E_Direction direction)
{
	// 回転角度を計算し、各三角形の向きを更新
	int8 rotate = (uint8)direction - (uint8)this->direction;
	this->direction = direction;
	for (auto& b : body)
	{
		b = b.rotatedAt(pos + CHIP_SIZE / 2.0, rotate * 90_deg);
	}
}

void MiniNeedle::restart()
{
	// 再起動時の処理（現在は何もしない）
}

bool MiniNeedle::intersectsPlayer()
{
	// いずれかの三角形とプレイヤーが交差しているか確認
	for (auto& b : body)
	{
		if (b.intersects(world.player.body))
		{
			return true;
		}
	}
	return false;
}

bool MiniNeedle::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void MiniNeedle::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	for (auto& b : body)
	{
		b.moveBy(pos - this->pos);
	}
	this->pos = pos;
}

void MiniNeedle::handleCollisionX()
{
	if (world.player.isAlive)
	{
		// プレイヤーが生きている場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void MiniNeedle::handleCollisionY()
{
	if (world.player.isAlive)
	{
		// プレイヤーが生きている場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void MiniNeedle::update()
{
	// 更新処理（現在は何もしない）
}

void MiniNeedle::draw() const
{
	// 各三角形を描画
	for (const auto& b : body)
	{
		b.draw().drawFrame(2, 0, Palette::Dimgrey);
	}
}

JumpToggleNeedle::JumpToggleNeedle(Vec2 pos, World& world, bool init, E_Direction direction)
	: Object{ pos, world, E_ObjectType::JumpToggleNeedle, U"ジャンプで切り替わる針" }
	, direction{ direction }
	, mouseOverBody{ RectF{ pos, CHIP_SIZE } }
	, body{ Triangle{ Vec2{ 0, CHIP_SIZE.y }, Vec2{ CHIP_SIZE.x / 2, 0 }, Vec2{ CHIP_SIZE } } }
	, init{ init }
	, isOn{ init }
{
	body.moveBy(pos);
	body = body.rotatedAt(pos + CHIP_SIZE / 2, (uint8)direction * 90_deg);
}

void JumpToggleNeedle::setDirection(E_Direction direction)
{
	// 回転角度を計算し、針の向きと形状を更新
	int8 rotate = (uint8)direction - (uint8)this->direction;
	this->direction = direction;
	body = body.rotatedAt(pos + CHIP_SIZE / 2, rotate * 90_deg);
}

void JumpToggleNeedle::restart()
{
	isOn = init;
}

bool JumpToggleNeedle::intersectsPlayer()
{
	return body.intersects(world.player.body);
}

bool JumpToggleNeedle::mouseOver()
{
	return mouseOverBody.mouseOver();
}

void JumpToggleNeedle::setPos(Vec2 pos)
{
	mouseOverBody.setPos(pos);
	body.moveBy(this->pos - pos);
	this->pos = pos;
}

void JumpToggleNeedle::setInit(bool init)
{
	this->init = init;
	this->isOn = init;
}

void JumpToggleNeedle::handleCollisionX()
{
	if (world.player.isAlive && isOn)
	{
		// プレイヤーが生きていて、針がオンの場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void JumpToggleNeedle::handleCollisionY()
{
	if (world.player.isAlive && isOn)
	{
		// プレイヤーが生きていて、針がオンの場合、死亡エフェクトを追加し、プレイヤーを死亡状態にする
		world.effect.add<DeathEffect>(world.player.body.center());
		world.player.isAlive = false;
	}
}

void JumpToggleNeedle::update()
{
	// プレイヤーがジャンプした時に針の状態を切り替える
	if (world.player.jumpNum < world.player.maxJumpNum && KeySpace.down() && world.player.isAlive)
	{
		isOn = !isOn; // 状態を反転
	}
}

void JumpToggleNeedle::draw() const
{
	// 針の状態に応じたテクスチャを描画
	TextureAsset((isOn ? U"JumpToggleNeedle" : U"JumpToggleNeedleAlpha")).resized(CHIP_SIZE).rotated((uint8)direction * 90_deg).draw(pos);
}
