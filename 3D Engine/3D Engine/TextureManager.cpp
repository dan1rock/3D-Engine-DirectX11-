#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager()
{
}

TexturePtr* TextureManager::createTextureFromFile(const wchar_t* path)
{
    return std::static_pointer_cast<Texture>(createResourceFromFile(path));
}

TextureManager::~TextureManager()
{
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
    return nullptr;
}
