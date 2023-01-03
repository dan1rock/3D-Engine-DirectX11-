#include "AppWindow.h"
#include "Vector3.h"
#include "Matrix.h"
#include <Windows.h>

struct vertex {
	Vector3 pos;
	Vector3 col;
};

__declspec(align(16))
struct constant {
	Matrix world;
	Matrix view;
	Matrix projection;
	unsigned int time;
};

AppWindow::AppWindow()
{
}

void AppWindow::updateDeltaTime()
{
	lastTickTime = currentTickTime;
	currentTickTime = ::GetTickCount64();
	deltaTime = (lastTickTime > 0) ? ((currentTickTime - lastTickTime) / 1000.0f) : 0;
}

void AppWindow::updatePosition()
{
	constant data = {};
	data.time = ::GetTickCount64();

	deltaPos += deltaTime * 1.0f;

	Matrix trans;

	trans.setTranslation(Vector3::lerp(Vector3(-1, -1, 0), Vector3(1, 1, 0), (cos(deltaPos) + 1.0f) / 2.0f));
	data.world.setScale(Vector3::lerp(Vector3(0.5f, 0.5f, 0), Vector3(1, 1, 0), (sin(deltaPos) + 1.0f) / 2.0f));

	data.world *= trans;
	
	data.view.setIdentity();
	RECT rc = this->getClientWindowRect();
	data.projection.setOrthoPM(
		(rc.right - rc.left) / 300.0f,
		(rc.bottom - rc.top) / 300.0f,
		-4.0f,
		4.0f
	);

	mConstantBuffer->update(GraphicsEngine::engine()->getImmDeviceContext(), &data);
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
		{Vector3(-0.5f, 0.5f, 0.0f)	,	Vector3(1, 0, 1)},
		{Vector3(0.5f, -0.5f, 0.0f)	,	Vector3(0, 1, 1)},
		{Vector3(0.7f, 0.3f, 0.0f)	,	Vector3(1, 1, 1)},
		{Vector3(0.9f, -0.2f, 0.0f)	,	Vector3(0, 1, 0)}
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

	this->updatePosition();

	GraphicsEngine::engine()->getImmDeviceContext()->setConstantBuffer(mVertexShader, mConstantBuffer);
	GraphicsEngine::engine()->getImmDeviceContext()->setConstantBuffer(mPixelShader, mConstantBuffer);

	GraphicsEngine::engine()->getImmDeviceContext()->setVertexShader(mVertexShader);
	GraphicsEngine::engine()->getImmDeviceContext()->setPixelShader(mPixelShader);
	GraphicsEngine::engine()->getImmDeviceContext()->setVertexBuffer(mVertexBuffer);
	GraphicsEngine::engine()->getImmDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexListSize(), 0);
	mSwapChain->present(false);

	updateDeltaTime();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	mSwapChain->release();
	mVertexBuffer->release();
	mVertexShader->release();
	mPixelShader->release();
	mConstantBuffer->release();
	GraphicsEngine::engine()->release();
}
