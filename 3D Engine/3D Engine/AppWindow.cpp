#include "AppWindow.h"

struct vector3 {
	float x, y, z;
};

struct vertex {
	vector3 pos;
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
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.7f, 0.3f, 0.0f},
		{0.9f, -0.2f, 0.0f}
	};

	mVertexBuffer = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->createShaders();

	void* shaderByteCode = nullptr;
	SIZE_T shaderSize = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "main", &shaderByteCode, &shaderSize);
	mVertexShader = GraphicsEngine::get()->createVertexShader(shaderByteCode, shaderSize);

	mVertexBuffer->load(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, shaderSize);

	GraphicsEngine::get()->releaseVertexShader();
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmDeviceContext()->clearRenderTarget(mSwapChain, 0, 0.3f, 0.4f, 1);
	RECT windowSize = this->getClientWindowRect();
	GraphicsEngine::get()->getImmDeviceContext()->setViewportSize(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::get()->getImmDeviceContext()->setVertexBuffer(mVertexBuffer);
	GraphicsEngine::get()->getImmDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	mSwapChain->release();
	mVertexBuffer->release();
	GraphicsEngine::get()->release();
}
