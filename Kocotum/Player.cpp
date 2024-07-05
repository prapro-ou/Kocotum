#include "Player.hpp"

Player::Player(Vec2 pos)
	: body{ RectF{ 40, 40 } }
	, pos{ pos }
	, respawnPos{ pos }
	, velocity{ Vec2{ 0, 0 } }
	, accelaration{ Vec2{ 0, 2000 } }
	, jumpNum{ 0 }
	, maxJumpNum{ 2 }
	, gravityDirection{ 1 }
	, isGravityReverse{ false }
	, isAlive{ true }
	, isOnGround{ false }
	, isFacingRight{ true }
{
	body.setPos(pos);
}

void Player::printInfo()
{
	// プレイヤーの現在の状態をコンソールに出力
	Print << U"pos              :" << pos;
	Print << U"respawnPos       :" << respawnPos;
	Print << U"velocity         :" << velocity;
	Print << U"accelaration     :" << accelaration;
	Print << U"jumpNum          :" << jumpNum;
	Print << U"maxJumpNum       :" << maxJumpNum;
	Print << U"gravityDirection :" << gravityDirection;
	Print << U"isGravityReverse :" << isGravityReverse;
	Print << U"isAlive          :" << isAlive;
	Print << U"isOnGround       :" << isOnGround;
	Print << U"isFacingRight    :" << isFacingRight;
}

void Player::restart()
{
	// プレイヤーの状態を初期状態にリセット
	pos = respawnPos;
	body.setPos(pos);
	velocity = Vec2{ 0, 0 };
	accelaration = Vec2{ 0, 2500 };
	jumpNum = 0;
	maxJumpNum = 2;
	gravityDirection = 1;
	isGravityReverse = false;
	isAlive = true;
	isOnGround = false;
	isFacingRight = true;
}

void Player::updatePositionX(Array<std::shared_ptr<Object>>& objects)
{
	// X軸方向の速度と位置を更新
	velocity.x += accelaration.x * Scene::DeltaTime();
	pos.x += velocity.x * Scene::DeltaTime();
	body.setPos(pos);

	// オブジェクトとの衝突判定とX軸方向の衝突処理
	for (auto& object : objects)
	{
		if (object->intersectsPlayer())
		{
			object->handleCollisionX();
		}
	}
}

void Player::updatePositionY(Array<std::shared_ptr<Object>>& objects)
{
	// Y軸方向の位置を更新（重力の影響を考慮）
	pos.y += velocity.y * gravityDirection * Scene::DeltaTime();
	body.setPos(pos);

	// 地面との接触状態をリセットし、オブジェクトとの衝突判定とY軸方向の衝突処理を行う
	isOnGround = false;
	for (auto& object : objects)
	{
		if (object->intersectsPlayer())
		{
			object->handleCollisionY();
		}
	}
}

void Player::update(Array<std::shared_ptr<Object>>& objects)
{
	// 重力加速度を設定
	accelaration.y = 2500;

	// 空中にいる場合、重力の影響を受ける
	if (not isOnGround)
	{
		velocity.y += accelaration.y * Scene::DeltaTime();
	}

	// 左右の移動処理
	if (KeyA.pressed())
	{
		velocity.x = Min(velocity.x, -350.0);
		isFacingRight = false;
	}

	if (KeyD.pressed())
	{
		velocity.x = Max(velocity.x, 350.0);
		isFacingRight = true;
	}

	// 左右のキーが押されていない場合、X軸方向の速度をゼロにする
	if (not KeyA.pressed() and not KeyD.pressed())
	{
		velocity.x = 0;
	}

	// ジャンプ処理
	if (KeySpace.down() and jumpNum < maxJumpNum)
	{
		if (jumpNum > 0)
		{
			velocity.y = -800;
		}
		jumpNum++;
	}

	// ジャンプの高さ調整（スペースキーを押し続けた場合）
	if (KeySpace.pressed() and jumpNum == 1)
	{
		if (KeySpace.pressedDuration() < 0.13s)
		{
			velocity.y = -600;
			isOnGround = false;
		}
	}

	// X軸とY軸の位置更新を実行
	updatePositionX(objects);
	updatePositionY(objects);
}

void Player::draw() const
{
	// プレイヤーの向きと重力の反転状態に応じてテクスチャを描画
	TextureAsset(U"Player").mirrored(not isFacingRight).flipped(isGravityReverse).resized(body.size).draw(pos);
}
