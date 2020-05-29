#include "stdafx.h"
#include "bullet.h"
missile::missile() {}
missile::~missile() {}
HRESULT missile::init(int bulletMax, float range)
{
	_bar = new Bar;
	_bar->init();

	anglebool = true;

	time = 0;
	missileCount = 0;
	
	_cannon.angle = PI/2;//90도
	_cannon.cannon = 80;//길이
	_cannon.center.x = 134;
	_cannon.center.y = 683;

	//_player = new player;

	windnum = 10;

	//사거리 초기화
	_range = range;

	//총알 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet5 bullet;
		//ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("images/캐논1번대포.bmp",WINSIZEX/2, WINSIZEY/2, 204, 52, 4, 1, true, RGB(255, 0, 255));
		bullet.exImage = new image;
		bullet.exImage->init("images/폭발효과.bmp", WINSIZEX / 2, WINSIZEY / 2, 1230, 160, 8, 1, true, RGB(255, 0, 255));
		bullet.speed = 0.0f;
		bullet.radius = 50;
		bullet.fire = false;
		bullet.isFire = false;
		bullet.isExp = false;
		bullet.isDamege = false;
		bullet.timeCount = 0.0f;
		bullet.gravity = 0.0f;
		_vBullet.push_back(bullet);

	}
	return S_OK;
}

void missile::release()
{
	SAFE_DELETE(_bar);
}

void missile::update(RECT playerRc)
{
	
	_bar->update();

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_cannon.angle += 0.05f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_cannon.angle -= 0.05f;
	}

	//포신 움직이는 각도
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;

}

void missile::render()
{
	_bar->render();

	//각도조절기 색깔
	HPEN Pen1, oPen;
	Pen1 = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	oPen = (HPEN)SelectObject(getMemDC(), Pen1);
	//각도 조절기 렌더
	LineMake(getMemDC(), _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);
	SelectObject(getMemDC(), oPen);
	DeleteObject(Pen1);

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire) continue;
		_viBullet->bulletImage->frameRender(getMemDC(),
			_viBullet->rc.left+50, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
		//EllipseMakeCenter(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->radius * 2, _viBullet->radius * 2); //대포알 실제크기 보기
	}

	//폭발효과 렌더설정
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isExp) continue;
			_viBullet->exImage->frameRender(getMemDC(),
			_viBullet->exrc.left+480, _viBullet->exrc.top,
			_viBullet->exImage->getFrameX(), 0);

			_viBullet->indexCount++;
			_viBullet->exImage->setFrameY(1);
			if (_viBullet->indexCount % 8 == 0)
			{
				_viBullet->indexCount = 0;
				_viBullet->index--;
				if (_viBullet->index < _viBullet->exImage->getMaxFrameY())
				{
					_viBullet->index = 8;
				}
				_viBullet->exImage->setFrameX(_viBullet->index);
			}
			//실제 크기보기
			//EllipseMakeCenter(getMemDC(), _viBullet->exrc[i].left+(_viBullet->exrc[i].right- _viBullet->exrc[i].left)/2, _viBullet->exrc[i].top + (_viBullet->exrc[i].bottom - _viBullet->exrc[i].top) / 2,32,32); //대포알 실제크기 보기
		
	}

	sprintf_s(str, "앵글 :  %.2f", _cannon.angle);
	TextOut(getMemDC(), WINSIZEX-200, 65, str, strlen(str));
}

void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->isFire)continue;
		_viBullet->isFire = true;
		_viBullet->anglebool = true;
		_viBullet->gravity = 0.f;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

float missile::getcannonAngle()
{
	return _cannon.angle;
}

void missile::move()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(_viBullet->isFire))continue;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
		
		_viBullet->angle = _cannon.angle;
		_viBullet->speed = _bar->getPower() * 0.02f;
		_viBullet->gravity += 0.05f;
	
		
		_viBullet->x += cosf(_cannon.angle) * _viBullet->speed + windnum * 0.3;
		_viBullet->y += -sinf(_cannon.angle) * _viBullet->speed + _viBullet->gravity;

	}
}

void missile::explosion()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(_viBullet->isExp))continue;
		
		_viBullet->exrc = RectMakeCenter(_viBullet->x+50 , _viBullet->y, _viBullet->exImage->getWidth(), _viBullet->exImage->getHeight());
	
	}

}
