#pragma once
#include <Siv3D.hpp>

/// @brief 底がnのlogを返します。
/// @param x 値
/// @param n 底
/// @return 値
double logN(double x, double n);


/// @brief 縦向きのスクロールバーを提供します。
class ScrollBarV
{
private:
	/// @brief スクロールバーの座標
	Vec2 pos;
	/// @brief スクロールバーの領域
	RectF Area;
	/// @brief スクロールバーのつまみ
	RectF Box;
	/// @brief スクロールバーが掴まれているかのフラグ
	bool grabbed;
	/// @brief 最大値
	double max;
	/// @brief 最小値
	double min;
	/// @brief 現在の値
	double now;

public:
	SIV3D_NODISCARD_CXX20
		ScrollBarV() = default;

	/// @brief 縦向きのスクロールバーを作成します。
	/// @param pos スクロールバーの座標
	/// @param width スクロールバーの幅
	/// @param height スクロールバーの高さ
	/// @param min 最小値
	/// @param max 最大値
	/// @param offset オフセット
	ScrollBarV(Vec2 pos, double width, double height, double min, double max);

	/// @brief スクロールバーが掴まれているかを返します。
	/// @return スクロールバーが掴まれている場合 true, それ以外の場合は false
	bool isGrabbed();

	/// @brief 最大値を設定します。
	/// @param max 最大値
	void setMax(double max);

	/// @brief 最小値を設定します。
	/// @param min 最小値
	void setMin(double min);

	/// @brief 現在の値を設定します。
	/// @param now 現在値
	void setNow(double now);

	/// @brief 最小値, 最大値, 現在の値を設定します。
	/// @param min 最小値
	/// @param max 最大値
	/// @param now 現在の値
	void setInfo(double min, double max, double now);

	/// @brief 現在の値を取得します。
	/// @return 現在の値
	double getNow();

	/// @brief スクロールバーを更新します。
	void update();

	/// @brief スクロールバーを描画します。
	void draw();

};
