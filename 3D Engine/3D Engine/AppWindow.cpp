#include "AppWindow.h"

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
}

void AppWindow::onUpdate()
{
	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	mSwapChain->release();
	GraphicsEngine::get()->release();
}
