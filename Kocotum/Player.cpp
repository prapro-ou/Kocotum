#include "Player.hpp"

Player::Player(Vec2 pos)
	: body{ RectF{ 40, 40 } }
	, pos{ pos }
	, respawnPos{ pos }
	, velocity{ Vec2{ 0, 0 } }
	, accelaration{ Vec2{ 0, 2000 } }
	, maxSpeed{ 350 }
	, jumpNum{ 0 }
	, maxJumpNum{ 2 }
	, gravityDirection{ 1 }
	, isGravityReverse{ false }
	, isAlive{ true }
	, isOnGround{ false }
	, isFacingRight{ true }
	, causeWarp{ false }
	, friction{ 0.2 }
	, velocityFriction{ 0 }
	, velocityClamp{ 0 }
{
	body.setPos(pos);
	gif.addGIF(U"idle", GIF(U"Idle.gif"));
	gif.addGIF(U"jumpUp", GIF(U"JumpUp.gif"));
	gif.addGIF(U"jumpDown", GIF(U"JumpDown.gif"));
	gif.addGIF(U"move", GIF(U"Move.gif"));
	gif.setActiveKey(U"idle");
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
	velocityFriction = 0;
	velocityClamp = 0;
}

void Player::updatePositionX(Array<std::shared_ptr<Object>>& objects)
{
	// X軸方向の速度と位置を更新
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
	accelaration.x = 2100;
	accelaration.y = 2500;

	// 横方向の入力
	// 右:1 左:-1 両方押されてるか両方押されてない:0
	int xInput = KeyD.pressed() - KeyA.pressed();

	// 空中にいる場合
	if (not isOnGround)
	{
		velocity.y += accelaration.y * Scene::DeltaTime();
		friction = 1.0;

		if (xInput == 0)
		{
			velocity.x = Math::SmoothDamp(velocity.x, 0.0, velocityFriction, 0.5);
		}

		if (velocity.y <= 0)
		{
			gif.setActiveKey(U"jumpUp");
		}
		else
		{
			gif.setActiveKey(U"jumpDown");
		}
	}
	else
	{
		if (xInput == 0)
		{
			velocity.x = Math::SmoothDamp(velocity.x, 0.0, velocityFriction, 1.01 - friction);
			gif.setActiveKey(U"idle");
		}
		else
		{
			gif.setActiveKey(U"move");
		}
	}

	// キー入力されているとき速度変更
	if (xInput != 0)
	{
		double rate = 1.0;
		if ((xInput >= 0) == !(velocity.x >= 0))
		{
			rate = 2.0;
		}
		velocity.x += xInput * accelaration.x * Scene::DeltaTime() * friction * rate;
	}

	velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);

	if (KeyA.pressed())
	{
		isFacingRight = false;
	}

	if (KeyD.pressed())
	{
		isFacingRight = true;
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
		if (KeySpace.pressedDuration() < 0.20s)
		{
			velocity.y = -500;
			isOnGround = false;
		}
	}

	if (isOnGround)
	{
		maxSpeed = 350;
	}

	// X軸とY軸の位置更新を実行
	updatePositionX(objects);
	updatePositionY(objects);
}

void Player::draw() const
{
	// プレイヤーの向きと重力の反転状態に応じてテクスチャを描画
	gif.getTexture().mirrored(not isFacingRight).flipped(isGravityReverse).resized(body.size).draw(pos);
}
