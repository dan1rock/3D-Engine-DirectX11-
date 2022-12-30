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
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	mVertexBuffer = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->createShaders();

	void* shaderByteCode = nullptr;
	UINT shaderSize = 0;

	GraphicsEngine::get()->getShaderBufferAndSize(&shaderByteCode, &shaderSize);

	mVertexBuffer->load(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, shaderSize);
}

void AppWindow::onUpdate()
{
	GraphicsEngine::get()->getImmDeviceContext()->clearRenderTarget(mSwapChain, 0, 0.3f, 0.4f, 1);
	RECT windowSize = this->getClientWindowRect();
	GraphicsEngine::get()->getImmDeviceContext()->setViewportSize(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmDeviceContext()->setVertexBuffer(mVertexBuffer);
	GraphicsEngine::get()->getImmDeviceContext()->drawTriangleList(mVertexBuffer->getVertexListSize(), 0);
	mSwapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	mSwapChain->release();
	mVertexBuffer->release();
	GraphicsEngine::get()->release();
}
