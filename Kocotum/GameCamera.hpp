#pragma once
#include <Siv3D.hpp>
#include "Player.hpp"

/**
 * @brief カメラの表示領域を表すクラス
 */
struct CameraArea
{
	/// @brief カメラの表示領域
	RectF area;
	/// @brief カメラ領域の位置
	Vec2 pos;
	/// @brief カメラを写す初期位置
	Vec2 initPos;
	/// @brief カメラの目標位置
	Vec2 cameraTargetPos;
	/// @brief カメラスクロール速度
	Vec2 velocity;
	/// @brief カメラ領域の幅と高さ
	double width, height;
	/// @brief カメラの倍率
	double scale;
	/// @brief スクロールするかどうか
	bool isScroll;

	/**
	 * @brief CameraAreaのコンストラクタ
	 * @param pos 領域の位置
	 * @param initPos 初期位置
	 * @param width 領域の幅
	 * @param height 領域の高さ
	 * @param velocity スクロール速度
	 * @param scale カメラのスケール
	 * @param isScroll スクロールするかどうか
	 */
	CameraArea(Vec2 pos, Vec2 initPos, double width = 1280, double height = 960, Vec2 velocity = Vec2(0, 0), double scale = 1.0, bool isScroll = false);

	void setPos(Vec2 pos);
	void setWidth(double width);
	void setHeight(double height);
	void restart();
	void update(const Player& player);
	void drawArea() const;
};

/**
 * @brief ゲームカメラを管理するクラス
 */
struct GameCamera
{
	Camera2D camera; ///< Siv3Dのカメラオブジェクト
	Array<std::shared_ptr<CameraArea>> areas; ///< カメラ領域のリスト
	std::shared_ptr<CameraArea> activeArea; ///< 現在アクティブなカメラ領域

	/**
	 * @brief GameCameraのコンストラクタ
	 */
	GameCamera();

	/**
	 * @brief カメラ領域を追加する
	 * @param area 追加するカメラ領域
	 */
	void addArea(std::shared_ptr<CameraArea> area);

	/**
	 * @brief プレイヤーが画面外にいるかチェックする
	 * @param player プレイヤーオブジェクト
	 * @return プレイヤーが画面外にいる場合true
	 */
	bool isPlayerOutOfScreen(const Player& player);

	/**
	 * @brief カメラをリスタートする
	 */
	void restart();

	void init();

	/**
	 * @brief カメラの状態を更新する
	 * @param player プレイヤーオブジェクト
	 */
	void update(const Player& player);

	/**
	 * @brief カメラ領域を描画する
	 */
	void drawArea() const;

	/**
	 * @brief カメラのTransformer2Dオブジェクトを作成する
	 * @return Transformer2Dオブジェクト
	 */
	Transformer2D createTransformer() const;
};
