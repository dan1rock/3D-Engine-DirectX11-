#pragma once
#include <d3d11.h>

class ResourceManager
{
public:
	ResourceManager();
	void createTexture(const wchar_t* path);
	~ResourceManager();
};

