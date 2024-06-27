# include <Siv3D.hpp> // Siv3D v0.6.14
# include "Object.hpp"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	while (System::Update())
	{
	}
}
