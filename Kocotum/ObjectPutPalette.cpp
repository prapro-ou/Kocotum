#include "ObjectPutPalette.hpp"

ObjectPutPalette::ObjectPutPalette(Vec2 pos, uint32 width, uint32 height)
    : pos{ pos }
    , body{ MSRenderTexture{width, height, Palette::Azure} }
	, world{ World{ Vec2{ 100, 100 } } }
{
    // レイアウトウィンドウの作成
    SelectObjectWindow layout{ Vec2{ 0, 0 }, U"レイアウト" };

    // 床・足場ウィンドウの作成と初期化
    SelectObjectWindow floor{ Vec2{ 0, 0 }, U"床・足場" };
    floor.addObject(std::make_shared<Wall>(pos, world));
    floor.addObject(std::make_shared<JumpToggleWall>(pos, world));

    // トラップウィンドウの作成と初期化
    SelectObjectWindow trap{ Vec2{ 0, 0 }, U"トラップ" };
    trap.addObject(std::make_shared<Needle>(pos, world));
    trap.addObject(std::make_shared<MiniNeedle>(pos, world));
    trap.addObject(std::make_shared<JumpToggleNeedle>(pos, world));

    // アイテムウィンドウの作成
    SelectObjectWindow item{ Vec2{ 0, 0 }, U"アイテム" };

    // 重力ウィンドウの作成と初期化
    SelectObjectWindow gravity{ Vec2{ 0, 0 }, U"重力" };
    gravity.addObject(std::make_shared<GravityLineHorizontal>(pos, world));
    gravity.addObject(std::make_shared<GravityLineVertical>(pos, world));

    // 作成したウィンドウをパレットに追加
    windows << layout << floor << trap << item << gravity;
}

Optional<E_ObjectType> ObjectPutPalette::getClickedType()
{
    Optional<E_ObjectType> result;

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
        double height = 0;

        // 各ウィンドウの位置を更新
        for (auto& window : windows)
        {
            window.pos = Vec2{ 0, height };
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
    }

    // 描画内容を確定
    Graphics2D::Flush();
    body.resolve();
    
    // パレットを描画
    body.draw(pos).drawFrame(2, Palette::Dimgray);
}
