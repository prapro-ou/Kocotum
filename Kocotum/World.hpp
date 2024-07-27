#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "Effect.hpp"
#include "Objects.hpp"
#include "GameCamera.hpp"
#include "PieMenu.hpp"

enum class Trojan : size_t
{
	Destroy = 0,
	Transparent = 1,
	Small = 2,
	JumpPlus = 3,
};

/**
 * @brief ゲームワールドを管理するクラス
 */
class World
{
public:
	/// @brief ワールド内のオブジェクトリスト
	Array<std::shared_ptr<Object>> objects;
	/// @brief プレイヤー
	Player player;
	/// @brief エフェクト
	Effect effect;
	/// @brief カメラ
	GameCamera camera;
	Stopwatch deathSw;
	bool causeWarp;
	String warpFileName;
	Array<PieMenuIcon> icons;
	std::unique_ptr<PieMenu> pieMenu;
	Array<bool> trojanEnable;
	Optional<size_t> trojanIndex;
	

	/**
	 * @brief Worldクラスのコンストラクタ
	 * @param pos プレイヤーの初期位置
	 */
	World(Vec2 pos);

	/// @brief Worldを初期化する
	void clear();

	/**
	 * @brief CSVファイルからワールドデータを読み込む
	 * @param fileName 読み込むCSVファイルの名前
	 */
	void loadWorld(String fileName);

	/**
	 * @brief ワールドデータをCSVファイルに保存する
	 * @param fileName 保存するCSVファイルの名前
	 */
	void saveWorld(String fileName);

	/**
	 * @brief ワールドにオブジェクトを追加する
	 * @param object 追加するオブジェクト
	 */
	void addObject(std::shared_ptr<Object> object);

	/**
	 * @brief ワールドをリスタートする
	 */
	void restart();

	void init();

	void warp();

	void killPlayer()
	{
		if (player.isAlive)
		{
			player.isAlive = false;
			deathSw.restart();
			effect.add<DeathEffect>(player.body.center());
		}
	}

	void savePlayer(Vec2 pos)
	{
		player.respawnPos = pos;;
	}

	/**
	 * @brief ワールドの状態を更新する
	 */
	void update();

	/**
	 * @brief ワールドを描画する
	 */
	void draw() const;
};
