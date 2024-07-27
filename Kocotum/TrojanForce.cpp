# include "TrojanForce.hpp"

TrojanForce::TrojanForce()
{
	icons =
	{
		PieMenuIcon{ Texture{ 0xF08EA_icon, 60 }, ColorF{ 0.86, 0.98, 0.80 }},
		PieMenuIcon{ Texture{ 0xF05B7_icon, 60 }, ColorF{ 0.60, 0.98, 0.60 }},
		PieMenuIcon{ Texture{ 0xF0485_icon, 60 }, ColorF{ 0.50, 1.00, 0.83 }},
		PieMenuIcon{ Texture{ 0xF033E_icon, 60 }, ColorF{ 1.00, 0.65, 0.00 }},
		PieMenuIcon{ Texture{ 0xF033E_icon, 60 }, ColorF{ 1.00, 0.65, 0.00 }},
	};
	enable = Array<bool>(4, false);
	index = none;
}

void TrojanForce::setEnable(size_t index, bool enable)
{
	this->enable[index] = enable;
}

void TrojanForce::update()
{
	if (MouseM.down())
	{
		pieMenu = std::make_unique<PieMenu>(icons, Scene::CenterF());
		pieMenu->setEnabled((size_t)Trojan::Destroy, enable[(size_t)Trojan::Destroy])
			.setEnabled((size_t)Trojan::Transparent, enable[(size_t)Trojan::Transparent])
			.setEnabled((size_t)Trojan::Small, enable[(size_t)Trojan::Small])
			.setEnabled((size_t)Trojan::JumpPlus, enable[(size_t)Trojan::JumpPlus])
			.setEnabled((size_t)Trojan::Lock, enable[(size_t)Trojan::Lock]);
	}

	if (pieMenu)
	{
		const Optional<int32> selected = pieMenu->update();

		if (MouseM.up())
		{
			if (selected)
			{
				index = (size_t)*selected;
			}
			pieMenu.reset();
		}
	}
}

void TrojanForce::draw() const
{
	if (pieMenu)
	{
		pieMenu->draw();
	}
}
