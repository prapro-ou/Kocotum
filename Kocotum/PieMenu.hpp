# include <Siv3D.hpp>

/// @brief パイメニュー用のアイコン
class PieMenuIcon
{
public:

	PieMenuIcon() = default;

	/// @brief パイメニュー用のアイコンを作成します。
	/// @param texture アイコンのテクスチャ
	/// @param color アイコンの描画色
	PieMenuIcon(const Texture& texture, const ColorF& color)
		: m_texture{ texture }
		, m_blurTexture{ m_texture.size(), ColorF{ 0.0, 1.0 } }
		, m_color{ color }
	{
		RenderTexture m_internalTexture{ m_texture.size() };

		// アイコンをやや小さめに描画する
		{
			const ScopedRenderTarget2D target{ m_blurTexture };
			m_texture.scaled(0.8).drawAt(m_blurTexture.size() * 0.5);
		}

		// ガウスぼかしを 2 回かける
		Shader::GaussianBlur(m_blurTexture, m_internalTexture, m_blurTexture);
		Shader::GaussianBlur(m_blurTexture, m_internalTexture, m_blurTexture);
	}

	void draw() const
	{
		// 背景のぼかした影を減算ブレンディングで描画する
		{
			const ScopedRenderStates2D blend{ BlendState::Subtractive };
			m_blurTexture.scaled(1.35).drawAt(Vec2{ 0, 0 }, ColorF{ 0.25 });
		}
		m_texture.drawAt(Vec2{ 0, 0 }, m_color);
	}

private:

	Texture m_texture;

	RenderTexture m_blurTexture;

	ColorF m_color;
};

/// @brief パイメニュークラス
class PieMenu
{
public:

	/// @brief パイメニューのスタイル
	struct Style
	{
		/// @brief パイメニューの外側の半径
		double outerRadius = 180.0;

		/// @brief パイメニューの内側の半径
		double innerRadius = 90.0;

		/// @brief アクティブなアイテムが外側に移動する距離
		double pieOuterOffset = 10.0;

		/// @brief アクティブなアイテムの枠の太さ
		double outlineThickness = 8.0;

		/// @brief パイメニューの色
		ColorF pieColor{ 0.0, 0.75 };

		/// @brief パイメニューの内側の枠の色
		ColorF pieInnerFrameColor{ 0.6 };

		/// @brief 無効なアイテムの色
		ColorF disabledPieColor{ 0.36, 0.4 };

		/// @brief アクティブなアイテムの色
		ColorF activePieColor{ 0.36, 0.84, 1.0 };

		/// @brief パイメニューの外側の枠の色
		ColorF activePieOutlineColor{ 1.0, 0.9, 0.2 };

		/// @brief アイテムを指す矢印の色
		ColorF arrowColor{ 1.0, 0.9, 0.2 };

		[[nodiscard]]
		static constexpr Style Default() noexcept
		{
			return{};
		}
	};

	SIV3D_NODISCARD_CXX20
		PieMenu() = default;

	/// @brief パイメニューを作成します。
	/// @param icons パイメニューのアイコン
	/// @param center パイメニューの中心座標
	/// @param style パイメニューのスタイル
	SIV3D_NODISCARD_CXX20
		PieMenu(const Array<PieMenuIcon>& icons, const Vec2& center, const Style& style = Style::Default())
		: m_itemCount{ static_cast<int32>(icons.size()) }
		, m_pieAngle{ Math::TwoPi / m_itemCount }
		, m_style{ style }
		, m_center{ center }
		, m_transitions{ icons.size(), Transition{ 0.1s, 0.2s } }
		, m_icons{ icons }
		, m_enabled(m_itemCount, true)
	{
		const Circle circle{ m_style.outerRadius - m_style.pieOuterOffset };
		const double activePieOffset = 0;
		const double outlineThicknessHalf = (m_style.outlineThickness * 0.5);

		{
			m_defaultPolygon = Polygon::CorrectOne(circle.arcAsPolygon((-m_pieAngle / 2), m_pieAngle, (m_style.outerRadius - m_style.innerRadius), 0.0).outer());
		}

		{
			m_innerOutline = m_defaultPolygon.calculateBuffer(-3).outer();
		}

		{
			const Array<Vec2> outline = circle.stretched(activePieOffset + outlineThicknessHalf)
				.arcAsPolygon((-m_pieAngle / 2), m_pieAngle, (m_style.outerRadius + activePieOffset - m_style.innerRadius + m_style.outlineThickness), 0.0).outer();

			// m_outlinePolygon の生成に失敗する確率を下げるためのおまじない
			{
				m_outlinePolygon = LineString{ outline.rotated(2) }.densified(4.0).calculateRoundBufferClosed(outlineThicknessHalf);

				if ((not m_outlinePolygon) || (not m_outlinePolygon.hasHoles()))
				{
					m_outlinePolygon = LineString{ outline.rotated(1) }.calculateRoundBufferClosed(outlineThicknessHalf);
				}
			}
		}
	}

	/// @brief パイメニューのアイテム数を返します。
	/// @return パイメニューのアイテム数
	[[nodiscard]]
	size_t size() const noexcept
	{
		return m_itemCount;
	}

	/// @brief パイメニューの指定したアイテムの有効・無効を設定します。
	/// @param index アイテムのインデックス
	/// @param enabled 有効にする場合 true, 無効にする場合は false
	/// @return *this
	PieMenu& setEnabled(size_t index, bool enabled) noexcept
	{
		m_enabled[index] = enabled;
		return *this;
	}

	/// @brief パイメニューの指定したアイテムが有効かを返します。
	/// @param index アイテムのインデックス
	/// @return アイテムが有効な場合 true, 無効な場合は false
	[[nodiscard]]
	bool getEnabled(size_t index) const noexcept
	{
		return m_enabled[index];
	}

	/// @brief パイメニューのアニメーションをリセットします。
	void reset() noexcept
	{
		m_selectedPie.reset();
		m_transitions.fill(Transition{ 0.1s, 0.2s });
	}

	/// @brief パイメニューを更新します。
	/// @return 選択されているアイテムのインデックス。選択されていない場合は none
	Optional<int32> update()
	{
		m_selectedPie.reset();

		const Vec2 cursorVector = (Cursor::PosF() - m_center).limitLengthSelf(Math::Lerp(m_style.innerRadius, m_style.outerRadius, 0.55));

		if (m_style.innerRadius <= cursorVector.length())
		{
			m_selectedPie = (static_cast<int32>((cursorVector.getAngle() + Math::TwoPi + (m_pieAngle / 2)) / m_pieAngle) % m_itemCount);
		}

		if (m_selectedPie && (not m_enabled[*m_selectedPie]))
		{
			m_selectedPie.reset();
		}

		for (int32 i = 0; i < m_itemCount; ++i)
		{
			const bool hovered = (i == m_selectedPie);
			m_transitions[i].update(hovered);
		}

		return m_selectedPie;
	}

	/// @brief パイメニューを描画します。
	void draw() const
	{
		for (int32 i = 0; i < m_itemCount; ++i)
		{
			const double centerAngle = (i * m_pieAngle);
			const bool hovered = (i == m_selectedPie);
			const Vec2 offset = Circular{ (m_style.pieOuterOffset + m_style.outlineThickness * m_transitions[i].value()), centerAngle };
			const Vec2 scalingCenter = Circular{ ((m_style.innerRadius + m_style.outerRadius) / 2), centerAngle };

			if (m_enabled[i])
			{
				{
					const Transformer2D transformer{ Mat3x2::Rotate(centerAngle).translated(m_center + offset) };
					m_defaultPolygon.draw(hovered ? m_style.activePieColor : m_style.pieColor);

					if (hovered)
					{
						m_outlinePolygon.draw(m_style.activePieOutlineColor);
					}
					else
					{
						m_innerOutline.drawClosed(m_style.pieInnerFrameColor);
					}
				}

				{
					const Vec2 iconOffset = Circular{ Math::Lerp(m_style.innerRadius, m_style.outerRadius, 0.53) + (m_style.outlineThickness * m_transitions[i].value()), centerAngle };
					const Transformer2D transformer{ Mat3x2::Translate(m_center + iconOffset) };
					m_icons[i].draw();
				}
			}
			else
			{
				const Transformer2D transformer{ Mat3x2::Rotate(centerAngle).translated(m_center + offset) };
				m_defaultPolygon.draw(m_style.disabledPieColor);

				if (hovered)
				{
					m_outlinePolygon.draw(m_style.activePieOutlineColor);
				}
			}
		}

		{
			const Vec2 cursorVector = (Cursor::PosF() - m_center).limitLengthSelf(Math::Lerp(m_style.innerRadius, m_style.outerRadius, 0.55));
			const double lineLength = Max(0.0, cursorVector.length() - (m_selectedPie ? 14 : 18));
			Line{ m_center, (m_center + cursorVector.withLength(lineLength)) }.draw(4, m_style.arrowColor);
			const Vec2 triangleCenter = (m_center + cursorVector);

			if (m_selectedPie)
			{
				Triangle{ triangleCenter, 12, cursorVector.getAngle() }.draw(m_style.arrowColor);
				Triangle{ triangleCenter, 26, cursorVector.getAngle() }.drawFrame(4, m_style.arrowColor);
			}
			else
			{
				Circle{ triangleCenter, 7 }.draw(m_style.arrowColor);
				Circle{ triangleCenter, 12 }.drawFrame(4, m_style.arrowColor);
			}
		}
	}

private:

	int32 m_itemCount = 0;

	double m_pieAngle = 0.0;

	Style m_style;

	Vec2 m_center{ 0, 0 };

	Polygon m_defaultPolygon;

	LineString m_innerOutline;

	Polygon m_outlinePolygon;

	Array<Transition> m_transitions;

	Array<PieMenuIcon> m_icons;

	Array<bool> m_enabled;

	Optional<int32> m_selectedPie;
};

