#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <iostream>

using namespace std;

SwapChain::SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->mD3dDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(&desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT create = GraphicsEngine::get()->mDxgiFactory->CreateSwapChain(device, &desc, &mSwapChain);
	if (FAILED(create))
		cout << "FAILED";

	return true;
}

bool SwapChain::release()
{
	mSwapChain->Release();
	delete this;
	return true;
}

SwapChain::~SwapChain()
{
}
