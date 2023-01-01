#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include <d3dcompiler.h>


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

	ID3D11DeviceContext* mImmContext = NULL;
	
	HRESULT create = 0;
	for (UINT index = 0; index < ARRAYSIZE(driverTypes);) {
		create = D3D11CreateDevice(NULL, driverTypes[index], NULL, NULL, featureLevels,
			ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mImmContext);
		if (SUCCEEDED(create)) break;

		++index;
	}
	if (FAILED(create))
		return false;

	mImmDeviceContext = new DeviceContext(mImmContext);

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

	mImmDeviceContext->release();
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

DeviceContext* GraphicsEngine::getImmDeviceContext()
{
	return this->mImmDeviceContext;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

VertexShader* GraphicsEngine::createVertexShader(const void* shaderBytecode, SIZE_T bytecodeLength)
{
	VertexShader* vs = new VertexShader();
	if (!vs->init(shaderBytecode, bytecodeLength)) {
		vs->release();
		return nullptr;
	};

	return vs;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* fileName, const char* entryPoint, void** shaderBytecode, SIZE_T* bytecodeLength)
{
	ID3DBlob* errblob = nullptr;
	if (FAILED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPoint, "vs_5_0", 0, 0, &mVSBlob, &errblob))) {
		if(errblob) errblob->Release();
		return false;
	};

	*shaderBytecode = mVSBlob->GetBufferPointer();
	*bytecodeLength = mVSBlob->GetBufferSize();

	return true;
}

void GraphicsEngine::releaseVertexShader()
{
	if(mVSBlob) mVSBlob->Release();
}

bool GraphicsEngine::createShaders()

{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &mPSBlob, &errblob);
	mD3dDevice->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), nullptr, &mPS);
	return true;
}


bool GraphicsEngine::setShaders()
{
	mImmDeviceContext->mDeviceContext->PSSetShader(mPS, nullptr, 0);
	return true;
}
