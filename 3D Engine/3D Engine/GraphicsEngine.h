#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	~GraphicsEngine();

	static GraphicsEngine* get();

	SwapChain* createSwapShain();
	DeviceContext* getImmDeviceContext();
	VertexBuffer* createVertexBuffer();
	VertexShader* createVertexShader(const void* shaderBytecode, SIZE_T bytecodeLength);

	bool compileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderBytecode, SIZE_T* bytecodeLength);
	void releaseVertexShader();

	bool createShaders();
	bool setShaders();
private:
	ID3D11Device* mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;
	DeviceContext* mImmDeviceContext;

	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFactory;

	ID3DBlob* mVSBlob;
	ID3DBlob* mPSBlob;

	ID3D11VertexShader* mVS;
	ID3D11PixelShader* mPS;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
};

