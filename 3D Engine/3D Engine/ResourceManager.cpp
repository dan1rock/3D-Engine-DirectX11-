#include "ResourceManager.h"
#include <string>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental\filesystem>
#include "DirectXTex.h"

ResourceManager::ResourceManager()
{
}

ResourcePtr* ResourceManager::createResourceFromFile(const wchar_t* path)
{
	std::wstring fullPath = std::experimental::filesystem::absolute(path);

	auto it = resourceMap.find(fullPath);

	if (it != resourceMap.end())
		return it->second;

	Resource* rawRes = this->createResourceFromFileConcrete(fullPath.c_str());

	if (rawRes)
	{
		ResourcePtr* res(rawRes);
		resourceMap[fullPath] = res;
		return res;
	}

	return nullptr;
}

ResourceManager::~ResourceManager()
{
}
