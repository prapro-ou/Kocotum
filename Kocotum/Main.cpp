# include <Siv3D.hpp> // Siv3D v0.6.14

# include "Edit.hpp"
# include "Game.hpp"

# include "PieMenu.hpp"



void Main()
{
	Window::Resize(1280, 960);


	FontAsset::Register(U"SelectObjectWindow", 35);
	FontAsset::Register(U"ObjectName", 15);
	FontAsset::Register(U"ObjectText", 40, Typeface::Bold);
	FontAsset::Register(U"SaveFont", 15, Typeface::Heavy);

	TextureAsset::Register(U"Player", U"player.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall", U"Wall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"IceWall", U"IceWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWall", U"JumpToggleWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWallAlpha", U"JumpToggleWallAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Needle", U"Needle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedle", U"JumpToggleNeedle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedleAlpha", U"JumpToggleNeedleAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"StartPoint", U"StartPoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"SavePoint", U"SavePoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor", U"OneWayFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"IceFloor", U"IceFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"MoveFloor", U"MoveFloor.png", TextureDesc::Mipped);



	App manager;
	manager.add<Edit>(U"Edit");
	manager.add<Game>(U"Game");


	const Array<PieMenuIcon> icons =
	{
		PieMenuIcon{ Texture{ 0xF08EA_icon, 60 }, ColorF{ 0.86, 0.98, 0.80 }},
		PieMenuIcon{ Texture{ 0xF05B7_icon, 60 }, ColorF{ 0.60, 0.98, 0.60 }},
		PieMenuIcon{ Texture{ 0xF0485_icon, 60 }, ColorF{ 0.50, 1.00, 0.83 }},
		PieMenuIcon{ Texture{ 0xF033E_icon, 60 }, ColorF{ 1.00, 0.65, 0.00 }},
	};

	std::unique_ptr<PieMenu> pieMenu;



	while (System::Update())
	{
		ClearPrint();

		// 右クリックされたらパイメニューを登場させる
		if (MouseL.down())
		{
			pieMenu = std::make_unique<PieMenu>(icons, Scene::CenterF());
		}

		// パイメニューがあれば
		if (pieMenu)
		{
			const Optional<int32> selected = pieMenu->update();

			pieMenu->draw();

			// 右クリックが離されたら、選択されたアイテムを表示する
			if (MouseL.up())
			{
				ClearPrint();
				Print << selected;
				pieMenu.reset();
			}
		}

		//if (not manager.update())
		//{
		//	break;
		//}
	}
}
