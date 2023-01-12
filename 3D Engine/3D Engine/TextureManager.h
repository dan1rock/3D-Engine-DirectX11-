#pragma once
#include "ResourceManager.h"

class TextureManager: public ResourceManager 
{
public:
	TextureManager();
	TexturePtr* createTextureFromFile(const wchar_t* path);
	~TextureManager();

	// Inherited via ResourceManager
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) override;
};

