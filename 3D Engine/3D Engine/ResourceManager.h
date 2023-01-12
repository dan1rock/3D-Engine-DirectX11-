#pragma once
#include <unordered_map>
#include <string>
#include <filesystem>
#include "Resource.h"
#include "Pointers.h"

class ResourceManager
{
public:
	ResourceManager();
	ResourcePtr* createResourceFromFile(const wchar_t* path);
	~ResourceManager();
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) = 0;
private:
	std::unordered_map<std::wstring, ResourcePtr*> resourceMap;
};

