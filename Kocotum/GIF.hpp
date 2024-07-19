# pragma once
# include <Siv3D.hpp>

class GIF
{
private:
	AnimatedGIFReader gif;
	Array<Image> images;
	Array<int32> delays;
	Array<Texture> textures;

public:
	GIF(String FileName)
		:gif{ AnimatedGIFReader{ FileName } }
	{
		gif.read(images, delays);
		textures = images.map([](const Image& image) { return Texture{ image }; });
		images.clear();
	}

	Texture getTexture() const
	{
		double t = Scene::Time();
		const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);

		return textures[frameIndex];
	}
};


class GIFManager
{
private:
	HashTable<String, GIF> gif;
	String activeKey = U"";

public:
	SIV3D_NODISCARD_CXX20
		GIFManager() = default;

	void addGIF(String key, const GIF& gif)
	{
		this->gif.emplace(key, gif);
	}

	void setActiveKey(String key)
	{
		activeKey = key;
	}

	Texture getTexture() const
	{
		return gif.at(activeKey).getTexture();
	}
};
