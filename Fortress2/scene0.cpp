#include "stdafx.h"
#include "scene0.h"
scene0::scene0()
{
}

scene0::~scene0()
{
}

HRESULT scene0::init()
{
	IMAGEMANAGER->addImage("기본배경", "images/기본배경.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}
void scene0::release()
{
}

void scene0::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//씬체인지
		SCENEMANAGER->changeScene("scene1");
	}
}

void scene0::render()
{
	IMAGEMANAGER->render("기본배경", getMemDC());
}
