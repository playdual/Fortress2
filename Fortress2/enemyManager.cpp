#include "stdafx.h"
#include "enemyManager.h"
#include"player.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	this->setMinion();

	_bullet = new bullet;
	_bullet->init("bullet", 10, 600);
	return S_OK;
}

void enemyManager::release()
{
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	//ufo ÃÑ¾Ë
	_bullet->update();




}

void enemyManager::render()
{
	_viMinion = _vMinion.begin();

	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo;
			ufo = new minion;
			ufo->init("ufo", PointMake(100 + j * 150, 100 + i * 100));
			_vMinion.push_back(ufo);
		}
	}
}

