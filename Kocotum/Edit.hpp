# pragma once
# include <Siv3D.hpp>
# include "Effect.hpp"
# include "Object.hpp"
# include "Player.hpp"
# include "Objects.hpp"
# include "World.hpp"
# include "GameData.hpp"
# include "GameCamera.hpp"
# include "SelectObjectWindow.hpp"
# include "ObjectPutPalette.hpp"
# include "ObjectSetPalette.hpp"
# include "CameraSetPalette.hpp"
# include "WorldEditPalette.hpp"

/// @brief 編集状態を表す列挙型
enum class E_EditState : uint8
{
	/// @brief オブジェクトを配置する状態
	PlacingObject,

	/// @brief オブジェクトを設定する状態
	SettingObject,

	/// @brief カメラを設定する状態
	SettingCamera,

	/// @brief ワールドを設定する状態
	SettingWorld
};

/// @brief エディターシーンを表すクラス
class Edit : public App::Scene
{
public:
	/// @brief コンストラクタ
	/// @param init 初期化データ
	Edit(const InitData& init);

	/// @brief 更新処理
	void update() override;

	/// @brief 描画処理
	void draw() const override;

private:
	/// @brief オブジェクトを作成する
	/// @param pos 作成位置
	void createObject(Vec2 pos);

	/// @brief 現在の状態に応じた更新処理を行う
	void updateCurrentState();

	/// @brief オブジェクト配置モードの更新処理
	void updatePlacingObject();

	/// @brief オブジェクトの配置と削除を行う
	void placeOrRemoveObjects();

	/// @brief オブジェクト設定モードの更新処理
	void updateSettingObject();

	/// @brief オブジェクトの選択と更新を行う
	void selectAndUpdateObject();

	/// @brief カメラ設定モードの更新処理
	void updateSettingCamera();

	/// @brief カメラエリアの更新処理
	void updateCameraAreas();

	/// @brief マウスがカメラエリア上にあるかチェックする
	/// @return マウスがカメラエリア上にある場合はtrue
	bool checkMouseOverCameraArea();

	/// @brief 必要に応じて新しいカメラエリアを追加する
	/// @param isMouseOverCameraArea マウスがカメラエリア上にあるかどうか
	void addNewCameraAreaIfNeeded(bool isMouseOverCameraArea);

	/// @brief 要求に応じてカメラエリアを削除する
	void removeCameraAreaIfRequested();

	/// @brief ワールド設定モードの更新処理
	void updateSettingWorld();

	/// @brief パレットボタンの更新処理
	void updatePaletteButtons();

	/// @brief シーン遷移のチェック
	void checkSceneTransition();

	/// @brief グリッド
	Grid<RectF> grid;

	/// @brief カメラ
	Camera2D camera;

	/// @brief 選択されているオブジェクトタイプ
	std::shared_ptr<Object> selectObjectType;

	/// @brief オブジェクト配置パレット
	ObjectPutPalette putPalette;

	/// @brief オブジェクト設定パレット
	ObjectSetPalette setPalette;

	/// @brief カメラ設定パレット
	CameraSetPalette cameraPalette;

	/// @brief ワールド編集パレット
	WorldEditPalette worldPalette;

	/// @brief 選択されているオブジェクト
	std::shared_ptr<Object> selectObject;

	/// @brief 選択されているカメラエリア
	std::shared_ptr<CameraArea> selectCamera;

	/// @brief 現在の編集状態
	E_EditState state;

	/// @brief パレットボタン
	Array<RectF> paletteButtons;

	/// @brief 編集ボックス
	RectF editBox;
};
