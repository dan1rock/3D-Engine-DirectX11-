#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class GraphicsEngine;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void clearRenderTarget(SwapChain* swapChain, float r, float g, float b, float a);
	void setVertexBuffer(VertexBuffer* vertexBuffer);
	void drawTriangleList(UINT vertexCount, UINT startIndex);
	void drawTriangleStrip(UINT vertexCount, UINT startIndex);
	void setViewportSize(UINT width, UINT height);
	bool release();
	~DeviceContext();
private:
	ID3D11DeviceContext* mDeviceContext;

	friend class GraphicsEngine;
};

