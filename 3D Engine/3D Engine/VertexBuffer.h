#pragma once
#include <d3d11.h>

class VertexBuffer
{
	VertexBuffer();
	bool load(void* vertList, UINT vertSize, UINT listSize, void* shaderByteCode, UINT byteShaderSize);
	bool release();
	~VertexBuffer();
private:
	UINT mVertSize;
	UINT mListSize;

	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mInputLayout;
};

