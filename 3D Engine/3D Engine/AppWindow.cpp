#include "AppWindow.h"
#include <Windows.h>

struct vector3 {
	float x, y, z;
};

struct vertex {
	vector3 pos;
	vector3 col;
};

__declspec(align(16))
struct constant {
	unsigned int time;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	GraphicsEngine::get()->init();
	mSwapChain = GraphicsEngine::get()->createSwapShain();

	RECT windowSize = this->getClientWindowRect();
	mSwapChain->init(this->mHwnd, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);

	vertex vertexList[] = {
		{-0.5f, -0.5f, 0.0f,	1, 1, 0},
		{-0.5f, 0.5f, 0.0f,		1, 1, 0},
		{0.5f, -0.5f, 0.0f,		1, 1, 0},
		{0.7f, 0.3f, 0.0f,		1, 1, 0},
		{0.9f, -0.2f, 0.0f,		1, 1, 0}
	};

	mVertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	mConstantBuffer = GraphicsEngine::get()->createConstantBuffer();

	void* shaderByteCode = nullptr;
	SIZE_T shaderSize = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &shaderSize);
	mVertexShader = GraphicsEngine::get()->createVertexShader(shaderByteCode, shaderSize);
	mVertexBuffer->load(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, shaderSize);
	GraphicsEngine::get()->releaseVertexShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "main", &shaderByteCode, &shaderSize);
	mPixelShader = GraphicsEngine::get()->createPixelShader(shaderByteCode, shaderSize);
	GraphicsEngine::get()->releasePixelShader();

	constant data = {};
	data.time = 0;
	mConstantBuffer->load(&data, sizeof(data));
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmDeviceContext()->clearRenderTarget(mSwapChain, 0, 0.3f, 0.4f, 1);
	RECT windowSize = this->getClientWindowRect();
	GraphicsEngine::get()->getImmDeviceContext()->setViewportSize(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);

	constant data = {};
	data.time = ::GetTickCount64();
	mConstantBuffer->update(GraphicsEngine::get()->getImmDeviceContext(), &data);
	GraphicsEngine::get()->getImmDeviceContext()->setConstantBuffer(mVertexShader, mConstantBuffer);
	GraphicsEngine::get()->getImmDeviceContext()->setConstantBuffer(mPixelShader, mConstantBuffer);

	GraphicsEngine::get()->getImmDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::get()->getImmDeviceContext()->setPixelShader(mPixelShader);
	GraphicsEngine::get()->getImmDeviceContext()->setVertexBuffer(mVertexBuffer);
	GraphicsEngine::get()->getImmDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	mVertexBuffer->release();
	mVertexShader->release();
	mPixelShader->release();
	GraphicsEngine::get()->release();
}
