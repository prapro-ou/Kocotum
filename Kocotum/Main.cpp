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

	TextureAsset::Register(U"Wall1", U"Wall1.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall2", U"Wall2.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall3", U"Wall3.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall4", U"Wall4.png", TextureDesc::Mipped);

	TextureAsset::Register(U"OneWayFloor1", U"OneWayFloor1.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor2", U"OneWayFloor2.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor3", U"OneWayFloor3.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor4", U"OneWayFloor4.png", TextureDesc::Mipped);

	TextureAsset::Register(U"IceWall", U"IceWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"SpeedWall", U"SpeedWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWall", U"JumpToggleWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWallAlpha", U"JumpToggleWallAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Needle", U"Needle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedle", U"JumpToggleNeedle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedleAlpha", U"JumpToggleNeedleAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"StartPoint", U"StartPoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"SavePoint", U"SavePoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"IceFloor", U"IceFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"MoveFloor", U"MoveFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Spring", U"Spring.png", TextureDesc::Mipped);



	App manager;
	manager.add<Edit>(U"Edit");
	manager.add<Game>(U"Game");



	while (System::Update())
	{
		ClearPrint();

		Print << U"Draw call の数: " << Profiler::GetStat().drawCalls;
		Print << U"三角形の描画回数: " << Profiler::GetStat().triangleCount;

		if (not manager.update())
		{
			break;
		}
	}
}
