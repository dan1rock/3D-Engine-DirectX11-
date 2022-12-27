#pragma once
#include <d3d11.h>

class SwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool init();
	bool release();
	~GraphicsEngine();

	static GraphicsEngine* get();

	SwapChain* createSwapShain();
private:
	ID3D11Device* mD3dDevice;
	D3D_FEATURE_LEVEL mFeatureLevel;
	ID3D11DeviceContext* mContext;

	IDXGIDevice* mDxgiDevice;
	IDXGIAdapter* mDxgiAdapter;
	IDXGIFactory* mDxgiFactory;

	friend class SwapChain;
};

