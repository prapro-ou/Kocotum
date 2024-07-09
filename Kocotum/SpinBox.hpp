# pragma once
# include <Siv3D.hpp>


/// @brief 数値を入力することができるUIスピンボックスを提供します。
class SpinBox
{
protected:
	/// @brief スピンボックスの座標
	Vec2 pos;
	/// @brief スピンボックスの幅
	double width;
	/// @brief スピンボックスの高さ
	double height;
	/// @brief フォントの大きさ
	uint16 fontSize;
	/// @brief フォント
	Font font;
	/// @brief スピンボックスの領域
	RectF region;
	/// @brief スピンボックスの値
	TextEditState value;
	/// @brief スピンボックスの最大桁数
	uint32 maxDigit;
	/// @brief カーソルを見せるかどうか(点滅)
	bool showCursor;
	/// @brief スピンボックスの最低幅
	const double MinWidth = 50;
	/// @brief 文字消去用のストップウォッチ
	Stopwatch backspaceStopwatch;
	/// @brief 利用可能かどうか
	bool enable;

	/// @brief カーソルの位置にある文字を消去した文字列を取得します。
	String deleteCursorPosText();

public:
	/// @brief デフォルトコンストラクターです。何もしません。
	SIV3D_NODISCARD_CXX20
		SpinBox() = default;

	/// @brief スピンボックスを作成します。
	/// @param pos 座標
	/// @param width 幅(最低50)
	/// @param height 高さ
	/// @param value 値
	/// @param maxDigit 最大桁数
	/// @param step 増減幅
	SpinBox(Vec2 pos, double width = 150, uint16 size = 50, uint32 maxDigit = 16, String value = U"0");

	/// @brief スピンボックスのTextEditStateを取得します。
	/// @return TextEditState
	TextEditState& getState();

	/// @brief スピンボックスの現在の値を取得します。
	/// @return スピンボックスの値が数値に変換できなければ0, それ以外は格納されている値
	int32 getValue();

	/// @brief スピンボックスの値を設定します。
	/// @param value 設定する値
	void setValue(double value);

	/// @brief スピンボックスが利用可能かどうかを設定します。
	/// @param enable 利用可能かどうかを設定する値
	void setEnable(bool enable);

	/// @brief スピンボックスが利用可能かどうかを取得します。
	/// @return 利用可能の場合 true, それ以外 false
	bool isEnable();

	/// @brief スピンボックスの座標を設定します。
	/// @param pos pos 設定する座標
	void setPos(Vec2 pos);

	/// @brief スピンボックスがアクティブかどうかを取得します。
	/// @return スピンボックスがアクティブの場合 true, それ以外 false
	bool isActive();

	/// @brief スピンボックスを更新します。
	void update();

	/// @brief スピンボックスを描画します。
	void draw() const;
};

