#include "SelectObjectWindow.hpp"

SelectObjectWindow::SelectObjectWindow(Vec2 pos, String title, double width)
	: pos{ pos }
	, title{ title }
	, nameBox{ RectF{ pos, width, 50 } }
	, contentBox{ RectF{ pos + Vec2{ 0, 50 }, width, 108 } }
	, isExpanded{ true }
{
	objectBox.clear();
	objects.clear();
}

double SelectObjectWindow::getHeight()
{
	return nameBox.h + (contentBox.h * isExpanded);
}

void SelectObjectWindow::addObject(std::shared_ptr<Object> object)
{
	// オブジェクトの位置を計算
	Vec2 tmp = pos + Vec2{ 12, 62 } + Vec2{ 96 * ((int)objectBox.size() % 4), 96 * (int)(objectBox.size() / 4) };
	objectBox << RectF{ tmp, 84 };
	object->setPos(tmp + Vec2{ 10, 10 });
	objects << object;

	// コンテンツボックスの高さを更新
	contentBox.h = 12 + 96 * ((int)objectBox.size() / 4 + 1);
}

Optional<E_ObjectType> SelectObjectWindow::getClickedType()
{
	Optional<E_ObjectType> result;

	if (isExpanded)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objectBox[i].leftClicked())
			{
				result = objects[i]->type;
			}
		}
	}

	return result;
}

void SelectObjectWindow::update()
{
	// ウィンドウの位置を更新
	nameBox.setPos(pos);
	contentBox.setPos(pos + Vec2{ 0, 50 });

	// オブジェクトの位置を更新
	for (int i = 0; i < objects.size(); i++)
	{
		Vec2 tmp = pos + Vec2{ 12, 62 } + Vec2{ 96 * (i % 4), 96 * (int)(i / 4) };
		objectBox[i].setPos(tmp);
		objects[i]->setPos(tmp + Vec2{ 10, 10 });
	}

	// ウィンドウの展開/折りたたみを切り替え
	if (nameBox.leftClicked())
	{
		isExpanded ^= true;
	}
}

void SelectObjectWindow::draw() const
{
	if (isExpanded)
	{
		// コンテンツボックスを描画
		contentBox.draw(Palette::Whitesmoke).drawFrame(2, 0, Palette::Dimgray);
		for (auto& ob : objectBox)
		{
			ob.rounded(5).draw(Palette::Gainsboro);
		}

		// オブジェクトを描画
		for (auto& object : objects)
		{
			object->draw();
		}
	}

	// タイトルボックスを描画
	nameBox.rounded(2).draw(Palette::Dodgerblue).drawFrame(2, 0, Palette::Dimgray);
	FontAsset(U"SelectObjectWindow")(title).draw(nameBox.movedBy(10, 0));
	if (nameBox.mouseOver())
	{
		nameBox.draw(ColorF(1, 1, 0, 0.25));
	}

	if (isExpanded)
	{
		// オブジェクトにマウスを乗せたときにその名前を表示させる
		for (int i = 0; i < objects.size(); i++)
		{
			if (objectBox[i].mouseOver())
			{
				objectBox[i].draw(ColorF(0.5, 1, 1, 0.25));
				RectF tmp{ Arg::bottomLeft(Cursor::PosF()), FontAsset(U"ObjectName")(objects[i]->name).region().w + 4, 25 };
				tmp.draw().drawFrame(2, Palette::Black);
				FontAsset(U"ObjectName")(objects[i]->name).draw(tmp.moveBy(2, 0), Palette::Black);
			}
		}
	}
}
