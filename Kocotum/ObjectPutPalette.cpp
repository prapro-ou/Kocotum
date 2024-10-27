#include "ObjectPutPalette.hpp"

ObjectPutPalette::ObjectPutPalette(Vec2 pos, uint32 width, uint32 height)
    : pos{ pos }
    , body{ MSRenderTexture{width, height, Palette::Azure} }
	, scroll{ ScrollBarV{ Vec2{ width - 89, -1 }, 28, (double)height - 2, 0, (double)height - 2 } }
	, scrollMax{ 2.0 }
	, targetScroll{ 0.0 }
	, world{ World{ Vec2{ 100, 100 } } }
{
    // レイアウトウィンドウの作成
    SelectObjectWindow layout{ Vec2{ 0, 0 }, U"レイアウト" };
	layout.addObject(std::make_shared<StartPoint>(pos, world));
	layout.addObject(std::make_shared<SavePoint>(pos, world));
	layout.addObject(std::make_shared<WarpPoint>(pos, world));

    // 床・足場ウィンドウの作成と初期化
    SelectObjectWindow floor{ Vec2{ 0, 0 }, U"床・足場" };
    floor.addObject(std::make_shared<Wall>(pos, world));
    floor.addObject(std::make_shared<QuarterWall>(pos, world));
    floor.addObject(std::make_shared<JumpToggleWall>(pos, world));
    floor.addObject(std::make_shared<IceWall>(pos, world));
    floor.addObject(std::make_shared<SpeedWall>(pos, world));
	floor.addObject(std::make_shared<OneWayFloor>(pos, world));
	//floor.addObject(std::make_shared<IceFloor>(pos, world));
	floor.addObject(std::make_shared<MoveFloor>(pos, world));
	floor.addObject(std::make_shared<TouchActiveFloor>(pos, world));

    // トラップウィンドウの作成と初期化
    SelectObjectWindow trap{ Vec2{ 0, 0 }, U"トラップ" };
    trap.addObject(std::make_shared<Needle>(pos, world));
    trap.addObject(std::make_shared<QuarterNeedle>(pos, world));
    trap.addObject(std::make_shared<MiniNeedle>(pos, world));
    trap.addObject(std::make_shared<JumpToggleNeedle>(pos, world));
	trap.addObject(std::make_shared<Spring>(pos, world));
	trap.addObject(std::make_shared<DangerWall>(pos, world));

    // アイテムウィンドウの作成
    SelectObjectWindow item{ Vec2{ 0, 0 }, U"アイテム" };
	item.addObject(std::make_shared<JumpItem>(pos, world));

    // 重力ウィンドウの作成と初期化
    SelectObjectWindow gravity{ Vec2{ 0, 0 }, U"重力" };
    gravity.addObject(std::make_shared<GravityLineHorizontal>(pos, world));
    gravity.addObject(std::make_shared<GravityLineVertical>(pos, world));

	SelectObjectWindow textImage{ Vec2{ 0, 0 }, U"テキスト・画像" };
	textImage.addObject(std::make_shared<Text>(pos, world, U"T"));
	textImage.addObject(std::make_shared<ImageObject>(pos, world));

	SelectObjectWindow trojan{ Vec2{ 0, 0 }, U"トロイフォース" };
	trojan.addObject(std::make_shared<TrojanDestroy>(pos, world));

    // 作成したウィンドウをパレットに追加
    windows << layout << floor << trap << item << gravity << textImage << trojan;
}

double ObjectPutPalette::getWindowsHeight()
{
	double result = 0;
	for (auto& window : windows)
	{
		result += window.getHeight();
	}

	return result;
}

Optional<std::shared_ptr<Object>> ObjectPutPalette::getClickedType()
{
    Optional<std::shared_ptr<Object>> result;

    {
        // パレットの位置に合わせて座標変換
        const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Translate(pos) };

        // 各ウィンドウでクリックされたオブジェクトタイプを確認
        for (auto& window : windows)
        {
            if (const auto res = window.getClickedType())
            {
                result = res;
            }
        }
    }

    return result;
}

void ObjectPutPalette::update()
{
    {
        // パレットの位置に合わせて座標変換
        const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Translate(pos) };

		scroll.setInfo(0, scrollMax, -1 * targetScroll);
		scroll.update();

		targetScroll = -1 * scroll.getNow();
		targetScroll -= Mouse::Wheel() * 25;

		scrollMax = getWindowsHeight();

		targetScroll = Clamp(targetScroll, -1 * scrollMax, 0.0);


		double height = 0;

        // 各ウィンドウの位置を更新
        for (auto& window : windows)
        {
            window.pos = Vec2{ 0, height + targetScroll };
            height += window.getHeight();

            window.update();
        }
    }
}

void ObjectPutPalette::draw() const
{
    // パレットの背景をクリア
    body.clear(Palette::Azure);

    {
        // パレットのテクスチャに描画
        const ScopedRenderTarget2D target{ body };
        const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Translate(pos) };
        
        // 各ウィンドウを描画
        for (const auto& window : windows)
        {
            window.draw();
        }

		scroll.draw();
    }

    // 描画内容を確定
    Graphics2D::Flush();
    body.resolve();
    
    // パレットを描画
    body.draw(pos).drawFrame(2, Palette::Dimgray);
}
