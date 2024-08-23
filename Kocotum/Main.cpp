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


	TextureAsset::Register(U"Wall1", U"data/img/object/Wall1.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall2", U"data/img/object/Wall2.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall3", U"data/img/object/Wall3.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall4", U"data/img/object/Wall4.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall5", U"data/img/object/Wall5.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Wall6", U"data/img/object/Wall6.png", TextureDesc::Mipped);

	TextureAsset::Register(U"OneWayFloor1", U"data/img/object/OneWayFloor1.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor2", U"data/img/object/OneWayFloor2.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor3", U"data/img/object/OneWayFloor3.png", TextureDesc::Mipped);
	TextureAsset::Register(U"OneWayFloor4", U"data/img/object/OneWayFloor4.png", TextureDesc::Mipped);

	TextureAsset::Register(U"IceWall", U"data/img/object/IceWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"SpeedWall", U"data/img/object/SpeedWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWall", U"data/img/object/JumpToggleWall.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleWallAlpha", U"data/img/object/JumpToggleWallAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Needle", U"data/img/object/Needle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedle", U"data/img/object/JumpToggleNeedle.png", TextureDesc::Mipped);
	TextureAsset::Register(U"JumpToggleNeedleAlpha", U"data/img/object/JumpToggleNeedleAlpha.png", TextureDesc::Mipped);
	TextureAsset::Register(U"StartPoint", U"data/img/object/StartPoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"SavePoint", U"data/img/object/SavePoint.png", TextureDesc::Mipped);
	TextureAsset::Register(U"IceFloor", U"data/img/object/IceFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"MoveFloor", U"data/img/object/MoveFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Spring", U"data/img/object/Spring.png", TextureDesc::Mipped);
	TextureAsset::Register(U"TouchActiveFloor", U"data/img/object/TouchActiveFloor.png", TextureDesc::Mipped);
	TextureAsset::Register(U"TouchActiveFloorActive", U"data/img/object/TouchActiveFloorActive.png", TextureDesc::Mipped);

	TextureAsset::Register(U"Background0", U"data/img/background/Background0.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Background1", U"data/img/background/Background1.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Background2", U"data/img/background/Background2.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Background3", U"data/img/background/Background3.png", TextureDesc::Mipped);
	TextureAsset::Register(U"Background4", U"data/img/background/Background4.png", TextureDesc::Mipped);



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
