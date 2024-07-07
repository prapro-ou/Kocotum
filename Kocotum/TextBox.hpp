# pragma once
# include <Siv3D.hpp>


/// @brief テキストを入力することができるUIを提供します。
class TextBox
{
private:
	/// @brief テキストボックスの座標
	Vec2 pos;
	/// @brief テキストボックスの幅
	double width;
	/// @brief テキストボックスの高さ
	double height;
	/// @brief フォントの大きさ
	uint16 fontSize;
	/// @brief フォント
	Font font;
	/// @brief テキストボックスの領域
	RectF region;
	/// @brief テキストボックスに入力されている値
	String value;
	/// @brief 編集中のテキスト
	String editingText;
	/// @brief テキストボックスが選択されているかどうか
	bool isActive;

public:
	/// @brief デフォルトコンストラクターです。何もしません。
	SIV3D_NODISCARD_CXX20
		TextBox() = default;

	/// @brief テキストボックスを作成します。
	/// @param pos 座標
	/// @param width 幅
	/// @param fontSize フォントのサイズ
	/// @param maxDigit 最大文字数
	/// @param value 初期値
	TextBox(Vec2 pos, double width = 350, uint16 fontSize = 50, String value = U"0");

	/// @brief テキストボックスの値を取得します。
	/// @return 入力されているテキスト
	String getText();

	/// @brief テキストボックスの値を設定します。
	/// @param text 設定するテキスト
	void setText(String text);

	/// @brief テキストボックスを更新します。
	void update();

	/// @brief テキストボックスを描画します。
	void draw() const;
};
