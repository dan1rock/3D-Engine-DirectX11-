#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow: public Window
{
public:
	AppWindow();
	void updateDeltaTime();
	void updatePosition();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* mSwapChain = nullptr;
	VertexBuffer* mVertexBuffer = nullptr;
	VertexShader* mVertexShader = nullptr;
	PixelShader* mPixelShader = nullptr;
	ConstantBuffer* mConstantBuffer = nullptr;
	IndexBuffer* mIndexBuffer = nullptr;

	float lastTickTime = 0;
	float currentTickTime = 0;
	float deltaTime = 0;

	float deltaPos = 0;
};

