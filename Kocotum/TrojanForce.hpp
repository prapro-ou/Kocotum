# pragma once

# include <Siv3D.hpp>
# include "PieMenu.hpp"

enum class Trojan : size_t
{
	Destroy = 0,
	Transparent = 1,
	Small = 2,
	JumpPlus = 3,
	Lock = 4,
};



class TrojanForce
{
public:
	Array<PieMenuIcon> icons;
	std::unique_ptr<PieMenu> pieMenu;
	Array<bool> enable;
	Optional<size_t> index;

	TrojanForce();

	void setEnable(size_t index, bool enable);

	void update();

	void draw() const;
};
