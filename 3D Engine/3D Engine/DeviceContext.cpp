#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) : mDeviceContext(deviceContext)
{
}

bool DeviceContext::clearRenderTarget(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT color[] = { r,g,b,a };
	mDeviceContext->ClearRenderTargetView(swapChain->mRenderTargetView, color);

	return true;
}

bool DeviceContext::release()
{
	mDeviceContext->Release();
	delete this;
	return true;
}

DeviceContext::~DeviceContext()
{
}
