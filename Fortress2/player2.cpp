#include "stdafx.h"
#include "player2.h"

#pragma warning(disable : 4996)

//cpp에 인클루드 해야 진정한 상호참조...
player2::player2()
{
}

player2::~player2()
{
}

HRESULT player2::init()
{

	drop = true;
	isBase = true;
	isLeft = false;
	isRight = false;
	isSpace = false;
	isSpaceUp = false;
	isShoot = false;
	isisFire = false;
	player2Arrow = true; // 마지막 입력이 true면 오른쪽, false면 왼쪽

	shootCount = 0;
	_player2 = IMAGEMANAGER->addFrameImage("player2", "images/캐논기본.bmp", 912, 91, 9, 1, true, RGB(255, 0, 255));
	_player2BaseLeft = IMAGEMANAGER->addFrameImage("player2BaseLeft", "images/캐논왼쪽기본.bmp", 912, 91, 9, 1, true, RGB(255, 0, 255));
	_player2Left = IMAGEMANAGER->addFrameImage("player2left", "images/캐논왼쪽이동.bmp", 731, 84, 7, 1, true, RGB(255, 0, 255));
	_player2Right = IMAGEMANAGER->addFrameImage("player2right", "images/캐논오른쪽이동.bmp", 731, 84, 7, 1, true, RGB(255, 0, 255));
	_player2Space = IMAGEMANAGER->addFrameImage("player2space", "images/캐논모으기.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	_player2LeftSpace = IMAGEMANAGER->addFrameImage("player2leftspace", "images/캐논왼쪽모으기.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	_player2SpaceUp = IMAGEMANAGER->addFrameImage("player2spaceUp", "images/캐논쏘기.bmp", 600, 87, 5, 1, true, RGB(255, 0, 255));
	_player2LeftSpaceUp = IMAGEMANAGER->addFrameImage("player2leftspaceUp", "images/캐논왼쪽쏘기.bmp", 600, 87, 5, 1, true, RGB(255, 0, 255));

	player2Rc = RectMake(WINSIZEX / 2+300, WINSIZEY / 2 - 300, 100, 83);


	_missile2 = new missile2;
	_missile2->init(50, 1000);


	_maxHP = _currentHP = 463;
	_hpBar = new progressBar2;
	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(_currentHP, _maxHP);


	//프로그래스
	_hpBar->setX(player2Rc.left + (player2Rc.right - player2Rc.left) / 2);
	_hpBar->setY(player2Rc.top + (player2Rc.bottom - player2Rc.top) / 2);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	//총알 구조체 초기화
	memset(_bullet, 0, sizeof(_bullet));

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].speed = 3.0f;
		_bullet[i].radius = 30.0f;
		_bullet[i].gravity = 0.0f;
		_bullet[i].isFire = false;
	}
	return S_OK;
}

void player2::release()
{
	SAFE_DELETE(_missile2);
	SAFE_DELETE(_hpBar);
}

void player2::update()
{
	_missile2->move();

	//프로그래스
	_hpBar->setX(player2Rc.left + (player2Rc.right - player2Rc.left) / 2 - 25);
	_hpBar->setY(player2Rc.top + (player2Rc.bottom - player2Rc.top) / 2 - 60);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		char temp[64];
		vector<string>vStr;

		vStr.push_back(_itoa(_currentHP, temp, 10));
		vStr.push_back(_itoa(_maxHP, temp, 10));
		vStr.push_back(_itoa(_player2->getX(), temp, 10));
		vStr.push_back(_itoa(_player2->getY(), temp, 10));

		TXTDATA->txtSave("save/player2Data.txt", vStr);
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		vector<string> vStr(TXTDATA->txtLoad("save/player2Data.txt"));

		_currentHP = stoi(vStr[0]);
		_maxHP = stoi(vStr[1]);
		_player2->setX(stoi(vStr[2]));
		_player2->setY(stoi(vStr[3]));
	}

	//플레이어
	if (isBase)
	{
		baseCount++;
		_player2->setFrameY(1);
		if (baseCount % 5 == 0)
		{
			baseCount = 0;
			baseIndex--;
			if (baseIndex < _player2->getMaxFrameY())
			{
				baseIndex = 9;
			}
			_player2->setFrameX(baseIndex);
		}
	}
	if (isBase && player2Arrow == false)
	{
		baseCount++;
		_player2BaseLeft->setFrameY(1);
		if (baseCount % 5 == 0)
		{
			baseCount = 0;
			baseIndex--;
			if (baseIndex < _player2BaseLeft->getMaxFrameY())
			{
				baseIndex = 9;
			}
			_player2BaseLeft->setFrameX(baseIndex);
		}
	}

	if (isLeft)
	{
		leftCount++;
		_player2Left->setFrameY(1);
		if (leftCount % 5 == 0)
		{
			leftCount = 0;
			leftIndex--;
			if (leftIndex < _player2Left->getMaxFrameY())
			{
				leftIndex = 7;
			}
			_player2Left->setFrameX(leftIndex);
		}
	}

	if (isRight)
	{
		rightCount++;
		_player2Right->setFrameY(1);
		if (rightCount % 5 == 0)
		{
			rightCount = 0;
			rightIndex--;
			if (rightIndex < _player2Right->getMaxFrameY())
			{
				rightIndex = 7;
			}
			_player2Right->setFrameX(rightIndex);
		}
	}

	if (isSpace)
	{
		spaceCount++;
		_player2Space->setFrameY(1);
		if (spaceCount % 5 == 0)
		{
			spaceCount = 0;
			spaceIndex--;
			if (spaceIndex < _player2Space->getMaxFrameY())
			{
				spaceIndex = 4;
			}
			_player2Space->setFrameX(spaceIndex);
		}
	}
	if (isSpace && player2Arrow == false)
	{
		spaceCount++;
		_player2LeftSpace->setFrameY(1);
		if (spaceCount % 5 == 0)
		{
			spaceCount = 0;
			spaceIndex--;
			if (spaceIndex < _player2LeftSpace->getMaxFrameY())
			{
				spaceIndex = 4;
			}
			_player2LeftSpace->setFrameX(spaceIndex);
		}
	}
	if (isSpaceUp)
	{
		spaceUpCount++;
		_player2SpaceUp->setFrameY(1);
		if (spaceUpCount % 5 == 0)
		{
			spaceUpCount = 0;
			spaceUpIndex--;
			if (spaceUpIndex < _player2SpaceUp->getMaxFrameY())
			{
				spaceUpIndex = 5;
			}
			_player2SpaceUp->setFrameX(spaceUpIndex);
		}
	}
	if (isSpaceUp && player2Arrow == false)
	{
		spaceUpCount++;
		_player2LeftSpaceUp->setFrameY(1);
		if (spaceUpCount % 5 == 0)
		{
			spaceUpCount = 0;
			spaceUpIndex--;
			if (spaceUpIndex < _player2LeftSpaceUp->getMaxFrameY())
			{
				spaceUpIndex = 5;
			}
			_player2LeftSpaceUp->setFrameX(spaceUpIndex);
		}
	}

	_missile2->update(player2Rc);
	_missile2->explosion();


	//collision();
}

void player2::render()
{
	//RectangleMake(getMemDC(), player2Rc.left, player2Rc.top, 99, 83);//캐릭터 렉트 보기

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire)continue;

		EllipseMakeCenter(getMemDC(), _bullet[i].x, _bullet[i].y,
			_bullet[i].radius * 2, _bullet[i].radius * 2);

	}


	if (isBase && player2Arrow == true)
	{
		_player2->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isBase && player2Arrow == false)
	{
		_player2BaseLeft->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isLeft)
	{
		_player2Left->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isRight)
	{
		_player2Right->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isSpace && player2Arrow == true)
	{
		_player2Space->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isSpace && player2Arrow == false)
	{
		_player2LeftSpace->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isSpaceUp && player2Arrow == true)
	{
		_player2SpaceUp->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}
	if (isSpaceUp && player2Arrow == false)
	{
		_player2LeftSpaceUp->frameRender(getMemDC(), player2Rc.left, player2Rc.top);
	}



	//_player2->render(getMemDC(), rc.left, rc.top);

	_missile2->render();
 
	//RectangleMakeCenter(getMemDC(), player2Rc.left, player2Rc.top,83 ,_player2->getHeight() );
	_hpBar->render();


}

void player2::draw()
{
	_player2->frameRender(getMemDC(), player2Rc.left, player2Rc.top, 9, 1);


}

RECT player2::getplayer2Rc()
{
	return player2Rc;
}

void player2::bulletFire()//캐논볼
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire)continue;

		_bullet[i].isFire = true;
		if (player2Arrow == true)
		{
			_bullet[i].x = cosf(_cannon.angle) * (getplayer2Rc().right - getplayer2Rc().left) + getplayer2Rc().right;//방향이 오른쪽일때 오른쪽으로 쏨
		}
		else if (player2Arrow == false)
		{
			_bullet[i].x = -cosf(_cannon.angle) * (getplayer2Rc().right - getplayer2Rc().left) + getplayer2Rc().left; //방향이 왼쪽일때 왼쪽으로 쏨
		}

		_bullet[i].y = -sinf(_cannon.angle) * (getplayer2Rc().bottom - getplayer2Rc().top) + getplayer2Rc().bottom - (getplayer2Rc().bottom - getplayer2Rc().top);
		_bullet[i].angle = _cannon.angle;
		break;
	}
}

void player2::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire)continue;

		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;
	}
}

void player2::setplayer2RcTopBottom(int rectTop, int rectBottom)
{
	player2Rc.top = rectTop;
	player2Rc.bottom = rectBottom;
}

void player2::setplayer2RcLeftRight(int rectLeft, int rectRight)
{
	player2Rc.left = rectLeft;
	player2Rc.right = rectRight;
}

void player2::setplayer2RcLeftRightAdd(int rectLeftAdd, int rectRightAdd)
{
	player2Rc.left = player2Rc.left + rectLeftAdd;
	player2Rc.right = player2Rc.right + rectRightAdd;

}

void player2::setdropbool(bool value)
{
	drop = value;
}

void player2::setGravity(int gravity)
{
	player2Rc.top += gravity;
	player2Rc.bottom += gravity;
}

void player2::hitDamage(float damage)
{
	_currentHP -= damage;
}

