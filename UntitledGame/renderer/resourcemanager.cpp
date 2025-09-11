#include "renderer/renderer.h"

#include "core/services.h"

#include <fstream>
#include <sstream>
#include <string>
#include <print>

std::string loadFile(const char* path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::printf("ERROR: Could not open file: %s\n", path);
		return "";
	}

	std::ostringstream contents;
	contents << file.rdbuf();

	std::string result = contents.str();
	std::printf("Loaded shader (%s): %zu characters\n", path, result.size());

	return result;
}

ShaderProgram* ResourceManager::loadShaders(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = loadFile(vertexPath);
	std::string fragmentCode = loadFile(fragmentPath);

	Renderer* renderer = Services::getService<Renderer>("Renderer");
	GPUResource* vs = renderer->createVertexShader(vertexCode.c_str());
	GPUResource* fs = renderer->createFragmentShader(fragmentCode.c_str());
	ShaderProgram* program = renderer->createShaderProgram(vs, fs);

	return program;
}