#pragma once
#include <Siv3D.hpp>
#include "Object.hpp"
#include "Player.hpp"
#include "Effect.hpp"
#include "Objects.hpp"
#include "GameCamera.hpp"

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

	/**
	 * @brief Worldクラスのコンストラクタ
	 * @param pos プレイヤーの初期位置
	 */
	World(Vec2 pos);

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

	/**
	 * @brief ワールドの状態を更新する
	 */
	void update();

	/**
	 * @brief ワールドを描画する
	 */
	void draw() const;
};
