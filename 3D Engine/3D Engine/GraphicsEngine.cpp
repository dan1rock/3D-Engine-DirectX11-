#include "GraphicsEngine.h"
#include "SwapChain.h"

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	
	HRESULT create = 0;
	for (UINT index = 0; index < ARRAYSIZE(driverTypes);) {
		create = D3D11CreateDevice(NULL, driverTypes[index], NULL, NULL, featureLevels,
			ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mContext);
		if (SUCCEEDED(create)) break;

		++index;
	}
	if (FAILED(create))
		return false;

	mD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mDxgiDevice);
	mDxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mDxgiAdapter);
	mDxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mDxgiFactory);

	return true;
}

bool GraphicsEngine::release()
{
	mDxgiDevice->Release();
	mDxgiAdapter->Release();
	mDxgiFactory->Release();

	mContext->Release();
	mD3dDevice->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::createSwapShain()
{
	return new SwapChain();
}
