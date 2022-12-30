#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

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
private:
	ID3D11Device* mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;
	DeviceContext* mImmDeviceContext;

	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFactory;

	friend class SwapChain;
	friend class VertexBuffer;
};

