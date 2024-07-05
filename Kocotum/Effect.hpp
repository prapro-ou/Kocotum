# pragma once
# include <Siv3D.hpp>

struct DeathEffect : IEffect
{
	Vec2 m_pos;

	explicit DeathEffect(const Vec2& pos)
		: m_pos{ pos } {}

	bool update(double t) override
	{
		double e = EaseOutCubic(t * 4);

		Circle{ m_pos, e * 100 }.drawFrame((1 - e) * 5);

		return t < 0.25;
	}
};
