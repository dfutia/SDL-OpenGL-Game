#include "renderer/renderer.h"
#include "core/services.h"

#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <print>

Texture::Texture(const std::string& path) : Resource(path)
{
	std::println("Loading texture from path: {}", path);
	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &mColorBit, STBI_rgb_alpha);

	if (data)
	{
		std::println("Texture loaded: {} ({}x{}, {} bits)", path, mWidth, mHeight, mColorBit);
		Renderer* renderer = Services::getService<Renderer>("Renderer");
		mGPUResource = renderer->createTexture(mWidth, mHeight, data);
		stbi_image_free(data);
	}
	else
	{
		std::println("Failed to load texture: {}", path);
	}
}

Texture::Texture(const std::vector<std::string>& paths) : Resource("cubmap")
{
}

Texture::~Texture()
{
}