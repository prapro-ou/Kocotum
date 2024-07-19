# include <Siv3D.hpp> // Siv3D v0.6.14

# include "Edit.hpp"
# include "Game.hpp"



void Main()
{
	Window::Resize(1280, 960);


	FontAsset::Register(U"SelectObjectWindow", 35);
	FontAsset::Register(U"ObjectName", 15);
	FontAsset::Register(U"ObjectText", 40, Typeface::Bold);

	TextureAsset::Register(U"Player", U"player.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall", U"Wall.png", TextureDesc::Mipped);
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


	while (System::Update())
	{
		ClearPrint();

		if (not manager.update())
		{
			break;
		}
	}
}
