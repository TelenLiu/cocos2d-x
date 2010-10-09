// Helloworld-win32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Helloworld-win32.h"

#include "cocos2d.h"
using namespace cocos2d;

#define IMG_PATH        "HelloWorld.png"

static HINSTANCE g_hInstance;

//////////////////////////////////////////////////////////////////////////
// implement MyLayer
//////////////////////////////////////////////////////////////////////////

class MyLayer : public CCLayer
{
public:
	virtual void onEnter()
	{
		CCLayer::onEnter();
		setIsTouchEnabled(true);
	}

	virtual bool ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
	{
		CCDirector::getSharedDirector()->end();
		return true;
	}

	virtual void registerWithTouchDispatcher(void)
	{
		CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(this,0,true);
	}
};

//////////////////////////////////////////////////////////////////////////
// implement HelloWorldApplication
//////////////////////////////////////////////////////////////////////////

bool HelloWorldApplication::initCocos2d()
{
	// init director
	CCDirector::getSharedDirector()->setOpenGLView(&m_MainForm);
	CCDirector::getSharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// load background image texture and get window size
	CCTexture2D * pTexture = CCTextureCache::sharedTextureCache()->addImage(IMG_PATH);
	CGSize size = CCDirector::getSharedDirector()->getWinSize();

	// create sprite instance
	CCSprite * pSprite = new CCSprite(); 
	pSprite->initWithTexture(pTexture);
	pSprite->setPosition(CGPoint(size.width / 2, size.height / 2));

	// create layer instance
	CCLayer * pLayer = new MyLayer();
	pLayer->addChild(pSprite);

	// add layer to scene
	CCScene * pScene = CCScene::node();
	pScene->addChild(pLayer);

	// add scene to director
	CCDirector::getSharedDirector()->runWithScene(pScene);

	pSprite->release();
	pLayer->release();
	return true;
}

bool HelloWorldApplication::InitInstance()
{
	m_MainForm.Create(L"HelloWorld", 320, 480);
// 	ShowWindow(m_MainForm.getHWnd(), SW_HIDE);
	return true;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInstance = hInstance;

	HelloWorldApplication app;
	if (app.InitInstance() && app.initCocos2d())
	{
		app.Run();
	}
	return 0;
}