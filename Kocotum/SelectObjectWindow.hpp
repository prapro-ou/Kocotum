#pragma once
#include <Siv3D.hpp>
#include "Effect.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Objects.hpp"

/// @brief オブジェクト選択ウィンドウクラス
class SelectObjectWindow
{
public:
	/// @brief ウィンドウの位置
	Vec2 pos;

	/// @brief ウィンドウのタイトル
	String title;

	/// @brief タイトル表示用の矩形
	RectF nameBox;

	/// @brief コンテンツ表示用の矩形
	RectF contentBox;

	/// @brief オブジェクト表示用の矩形の配列
	Array<RectF> objectBox;

	/// @brief オブジェクトの配列
	Array<std::shared_ptr<Object>> objects;

	/// @brief ウィンドウが展開されているかどうか
	bool isExpanded;

	/// @brief コンストラクタ
	/// @param pos ウィンドウの位置
	/// @param title ウィンドウのタイトル
	/// @param width ウィンドウの幅
	SelectObjectWindow(Vec2 pos, String title, double width = 400);

	/// @brief ウィンドウの高さを取得する
	/// @return ウィンドウの高さ
	double getHeight();

	/// @brief オブジェクトを追加する
	/// @param object 追加するオブジェクト
	void addObject(std::shared_ptr<Object> object);

	/// @brief クリックされたオブジェクトタイプを取得する
	/// @return クリックされたオブジェクトタイプ（Optional）
	Optional<std::shared_ptr<Object>> getClickedType();

	/// @brief ウィンドウの状態を更新する
	void update();

	/// @brief ウィンドウを描画する
	void draw() const;

private:
};
