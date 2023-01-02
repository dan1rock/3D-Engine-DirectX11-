#include "AppWindow.h"
#include "Vector3.h"
#include <Windows.h>

struct vertex {
	Vector3 pos;
	Vector3 col;
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
	GraphicsEngine::engine()->init();
	mSwapChain = GraphicsEngine::engine()->createSwapShain();

	RECT windowSize = this->getClientWindowRect();
	mSwapChain->init(this->mHwnd, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);

	vertex vertexList[] = {
		{Vector3(-0.5f, -0.5f, 0.0f),	Vector3(1, 1, 0)},
		{Vector3(-0.5f, 0.5f, 0.0f)	,	Vector3(1, 1, 0)},
		{Vector3(0.5f, -0.5f, 0.0f)	,	Vector3(1, 1, 0)},
		{Vector3(0.7f, 0.3f, 0.0f)	,	Vector3(1, 1, 0)},
		{Vector3(0.9f, -0.2f, 0.0f)	,	Vector3(1, 1, 0)}
	};

	mVertexBuffer = GraphicsEngine::engine()->createVertexBuffer();
	mConstantBuffer = GraphicsEngine::engine()->createConstantBuffer();

	void* shaderByteCode = nullptr;
	SIZE_T shaderSize = 0;

	GraphicsEngine::engine()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &shaderSize);
	mVertexShader = GraphicsEngine::engine()->createVertexShader(shaderByteCode, shaderSize);
	mVertexBuffer->load(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, shaderSize);
	GraphicsEngine::engine()->releaseVertexShader();

	GraphicsEngine::engine()->compilePixelShader(L"PixelShader.hlsl", "main", &shaderByteCode, &shaderSize);
	mPixelShader = GraphicsEngine::engine()->createPixelShader(shaderByteCode, shaderSize);
	GraphicsEngine::engine()->releasePixelShader();

	constant data = {};
	data.time = 0;
	mConstantBuffer->load(&data, sizeof(data));
}

void AppWindow::onUpdate()
{
	GraphicsEngine::engine()->getImmDeviceContext()->clearRenderTarget(mSwapChain, 0, 0.3f, 0.4f, 1);
	RECT windowSize = this->getClientWindowRect();
	GraphicsEngine::engine()->getImmDeviceContext()->setViewportSize(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);

	constant data = {};
	data.time = ::GetTickCount64();
	mConstantBuffer->update(GraphicsEngine::engine()->getImmDeviceContext(), &data);
	GraphicsEngine::engine()->getImmDeviceContext()->setConstantBuffer(mVertexShader, mConstantBuffer);
	GraphicsEngine::engine()->getImmDeviceContext()->setConstantBuffer(mPixelShader, mConstantBuffer);

	GraphicsEngine::engine()->getImmDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::engine()->getImmDeviceContext()->setPixelShader(mPixelShader);
	GraphicsEngine::engine()->getImmDeviceContext()->setVertexBuffer(mVertexBuffer);
	GraphicsEngine::engine()->getImmDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	mVertexBuffer->release();
	mVertexShader->release();
	mPixelShader->release();
	GraphicsEngine::engine()->release();
}
