# pragma once
# include <Siv3D.hpp>

struct DeathEffect : IEffect
{
	struct Trigon
	{
		Vec2 basepos;
		double r;
		double angle;
		double scale;
		int max;
		bool reverse;
		ColorF color;
	};

	Vec2 m_pos;
	Array<Trigon> m_trigons;

	explicit DeathEffect(const Vec2& pos)
		: m_pos{ pos }
	{
		for (auto i : step(5))
		{
			Trigon trigon
			{
				.basepos = pos,
				.r = 0,
				.angle = Random(360_deg),
				.scale = 0,
				.max = 30 + Random(-3, 3),
				.reverse = RandomBool(),
				.color = ColorF(0.5, 0.7, 1),
			};
			m_trigons << trigon;
		}
	}

	void drawTrigon(double t)
	{
		const double e = EaseOutExpo(t);
		double r = e * 23 + t * 5;

		for (auto trigon : m_trigons)
		{
			if (t < 0.2)
			{
				trigon.scale = t * trigon.max;
				trigon.color = ColorF(0.5, 0.7, 1, 1);
			}
			else
			{
				trigon.scale = trigon.max - (t - 0.2) * trigon.max;
				if (t < 0.4)	trigon.color = ColorF(0.5, 0.7, 1, 1);
				else trigon.color = ColorF(0.4, 0.6, 1, 0.3 + 0.7 * Periodic::Square0_1(0.1));
			}
			Triangle{ OffsetCircular{ m_pos, r * 0.8 + t * 30, trigon.angle }, trigon.scale, trigon.reverse * 180_deg }.draw(trigon.color);
		}
	}

	bool update(double t) override
	{
		double e = EaseOutCubic(t * 4);

		Circle{ m_pos, e * 100 }.drawFrame((1 - e) * 5, ColorF(0.5, 0.7, 1));
		drawTrigon(e);

		return t < 0.25;
	}
};

struct SavedEffect : IEffect
{
	Vec2 m_pos;

	explicit SavedEffect(const Vec2& pos)
		: m_pos{ pos } {}

	bool update(double t) override
	{
		double e = EaseOutQuint(t);
		double a = EaseInCirc(t);

		FontAsset(U"SaveFont")(U"SAVED!").drawAt(m_pos + Vec2{0, e * -64}, Palette::Yellow.withAlpha(255 - a * 255));

		return t < 1.0;
	}
};

struct EXEffect : IEffect
{
	// 軌跡用のテクスチャ
	const Texture m_texture{ U"example/particle.png", TextureDesc::Mipped };
	// 点の基本寿命（秒）
	const double LifeTime = 0.25;
	// 軌跡
	Array<TrailMotion> trails;
	// 軌跡の初期座標
	Vec2 m_pos;
	// ずらす
	Array<Vec2> offset;

	EXEffect(const Vec2& pos)
		:m_pos{ pos }
	{
		for (auto i : step(10))
		{
			offset << RandomVec2(50);
			trails << TrailMotion{}
				.setLifeTime(LifeTime)
				.setPositionFunction([this, i](double t) { return m_pos + offset[i] - Vec2{ 0, Scene::Height() * 10 * Max(t - i * 0.015, 0.0) } + Vec2{ 0, 100 }; })
				.setSizeFunction([i](double t) { return 40 * Sin(Max(t - i * 0.015, 0.0) * Math::Pi); })
				.setColor(Palette::Lime.withAlpha(150));
		}
	}

	bool update(double t) override
	{
		// 通常のTrail描画
		{
			for (auto& trail : trails)
			{
				trail.update();
				trail.draw(m_texture);
			}
		}
		return t < 1.0;
	}
};


struct ToggleEffect : IEffect
{
	struct Particle
	{
		Vec2 start;

		Vec2 velocity;

		double alpha;
	};
	Array<Particle> m_particles;
	Vec2 center;
	explicit ToggleEffect(const Vec2& start)
		: m_particles(Random(1, 4)),
		center(start)
	{
		for (auto& particle : m_particles)
		{
			const Vec2 vec = RandomVec2(40.0);
			particle.start = start + vec;

			particle.velocity = vec * Random(0.5, 1.0);

			particle.alpha = Random(0.4, 1.0);
		}
	}

	bool update(double t) override
	{
		t *= 1.5;
		for (const auto& particle : m_particles)
		{
			const Vec2 pos = particle.start
				+ particle.velocity * EaseOutQuad(t);

			RectF{ pos, 10.0 }.draw(ColorF(1, 0.25, 0.25, particle.alpha * (1 - EaseInQuad(t))));
		}
		RectF{ Arg::center(center),50 + EaseOutExpo(t) * 25 }.rotated(45_deg).drawFrame(1, ColorF(1, 0.25, 0.25, 0.5 - EaseInQuad(t) * 0.5));
		RectF{ Arg::center(center),50 + EaseOutQuart(t) * 25 }.rotated(45_deg).drawFrame(1, ColorF(1, 0.25, 0.25, 0.5 - EaseInQuad(t) * 0.5));
		RectF{ Arg::center(center),50 + EaseOutSine(t) * 25 }.rotated(45_deg).drawFrame(1, ColorF(1, 0.25, 0.25, 0.5 - EaseInQuad(t) * 0.5));
		return (t < 1.0);
	}
};
