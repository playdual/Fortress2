#include "stdafx.h"
#include "player.h"

#pragma warning(disable : 4996)

//cpp에 인클루드 해야 진정한 상호참조...
player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{

	drop = true;
	isBase = true;
	isLeft = false;
	isRight = false;
	isSpace = false;
	isSpaceUp = false;
	isShoot = false;
	isisFire = false;
	playerArrow = true; // 마지막 입력이 true면 오른쪽, false면 왼쪽

	shootCount = 0;
	_player = IMAGEMANAGER->addFrameImage("player", "images/캐논기본.bmp", 912, 91, 9, 1, true, RGB(255, 0, 255));
	_playerBaseLeft = IMAGEMANAGER->addFrameImage("playerBaseLeft", "images/캐논왼쪽기본.bmp", 912, 91, 9, 1, true, RGB(255, 0, 255));
	_playerLeft = IMAGEMANAGER->addFrameImage("playerleft", "images/캐논왼쪽이동.bmp", 731, 84, 7, 1, true, RGB(255, 0, 255));
	_playerRight = IMAGEMANAGER->addFrameImage("playerright", "images/캐논오른쪽이동.bmp", 731, 84, 7, 1, true, RGB(255, 0, 255));
	_playerSpace = IMAGEMANAGER->addFrameImage("playerspace", "images/캐논모으기.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	_playerLeftSpace = IMAGEMANAGER->addFrameImage("playerleftspace", "images/캐논왼쪽모으기.bmp", 400, 80, 4, 1, true, RGB(255, 0, 255));
	_playerSpaceUp = IMAGEMANAGER->addFrameImage("playerspaceUp", "images/캐논쏘기.bmp", 600, 87, 5, 1, true, RGB(255, 0, 255));
	_playerLeftSpaceUp = IMAGEMANAGER->addFrameImage("playerleftspaceUp", "images/캐논왼쪽쏘기.bmp", 600, 87, 5, 1, true, RGB(255, 0, 255));
	
	playerRc = RectMake(WINSIZEX/2, WINSIZEY/2-300, 100, 83);
	
	
	_missile = new missile;
	_missile->init(50, 1000);

	



	_maxHP = _currentHP = 463;
	_hpBar = new progressBar;
	_hpBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 0, 0, 50, 10);
	_hpBar->setGauge(_currentHP, _maxHP);


	//프로그래스
	_hpBar->setX(playerRc.left+(playerRc.right-playerRc.left)/2);
	_hpBar->setY(playerRc.top + (playerRc.bottom-playerRc.top)/2);
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

void player::release()
{
	SAFE_DELETE(_missile);
	SAFE_DELETE(_hpBar);
}

void player::update()
{
	
	_missile->move();
	//프로그래스
	_hpBar->setX(playerRc.left+(playerRc.right-playerRc.left)/2-25);
	_hpBar->setY(playerRc.top + (playerRc.bottom - playerRc.top) / 2-60);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		char temp[64];
		vector<string>vStr;

		vStr.push_back(_itoa(_currentHP, temp, 10));
		vStr.push_back(_itoa(_maxHP, temp, 10));
		vStr.push_back(_itoa(_player->getX(), temp, 10));
		vStr.push_back(_itoa(_player->getY(), temp,10));

		TXTDATA->txtSave("save/playerData.txt", vStr);
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		vector<string> vStr (TXTDATA->txtLoad("save/playerData.txt"));

		_currentHP = stoi(vStr[0]);
		_maxHP = stoi(vStr[1]);
		_player->setX(stoi(vStr[2]));
		_player->setY(stoi(vStr[3]));
	}

	//플레이어
	if (isBase)
	{
		baseCount++;
		_player->setFrameY(1);
		if (baseCount % 5 == 0)
		{
			baseCount = 0;
			baseIndex--;
			if (baseIndex < _player->getMaxFrameY())
			{
				baseIndex = 9;
			}
			_player->setFrameX(baseIndex);
		}
	}
	if (isBase&&playerArrow==false)
	{
		baseCount++;
		_playerBaseLeft->setFrameY(1);
		if (baseCount % 5 == 0)
		{
			baseCount = 0;
			baseIndex--;
			if (baseIndex < _playerBaseLeft->getMaxFrameY())
			{
				baseIndex = 9;
			}
			_playerBaseLeft->setFrameX(baseIndex);
		}
	}

	if (isLeft)
	{
		leftCount++;
		_playerLeft->setFrameY(1);
		if (leftCount % 5 == 0)
		{
			leftCount = 0;
			leftIndex--;
			if (leftIndex < _playerLeft->getMaxFrameY())
			{
				leftIndex = 7;
			}
			_playerLeft->setFrameX(leftIndex);
		}
	}

	if (isRight)
	{
		rightCount++;
		_playerRight->setFrameY(1);
		if (rightCount % 5 == 0)
		{
			rightCount = 0;
			rightIndex--;
			if (rightIndex < _playerRight->getMaxFrameY())
			{
				rightIndex = 7;
			}
			_playerRight->setFrameX(rightIndex);
		}
	}

	if (isSpace)
	{
		spaceCount++;
		_playerSpace->setFrameY(1);
		if (spaceCount % 5 == 0)
		{
			spaceCount = 0;
			spaceIndex--;
			if (spaceIndex < _playerSpace->getMaxFrameY())
			{
				spaceIndex = 4;
			}
			_playerSpace->setFrameX(spaceIndex);
		}
	}
	if (isSpace&&playerArrow==false)
	{
		spaceCount++;
		_playerLeftSpace->setFrameY(1);
		if (spaceCount % 5 == 0)
		{
			spaceCount = 0;
			spaceIndex--;
			if (spaceIndex < _playerLeftSpace->getMaxFrameY())
			{
				spaceIndex = 4;
			}
			_playerLeftSpace->setFrameX(spaceIndex);
		}
	}
	if (isSpaceUp)
	{
		spaceUpCount++;
		_playerSpaceUp->setFrameY(1);
		if (spaceUpCount % 5 == 0)
		{
			spaceUpCount = 0;
			spaceUpIndex--;
			if (spaceUpIndex < _playerSpaceUp->getMaxFrameY())
			{
				spaceUpIndex = 5;
			}
			_playerSpaceUp->setFrameX(spaceUpIndex);
		}
	}
	if (isSpaceUp&&playerArrow==false)
	{
		spaceUpCount++;
		_playerLeftSpaceUp->setFrameY(1);
		if (spaceUpCount % 5 == 0)
		{
			spaceUpCount = 0;
			spaceUpIndex--;
			if (spaceUpIndex < _playerLeftSpaceUp->getMaxFrameY())
			{
				spaceUpIndex = 5;
			}
			_playerLeftSpaceUp->setFrameX(spaceUpIndex);
		}
	}

	_missile->update(playerRc);
	_missile->explosion(); 

	//collision();
}

void player::render()
{
	//RectangleMake(getMemDC(), playerRc.left, playerRc.top, 99, 83);//캐릭터 렉트 보기
	
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire)continue;

		EllipseMakeCenter(getMemDC(), _bullet[i].x, _bullet[i].y,
			_bullet[i].radius * 2, _bullet[i].radius * 2);

	}


	if (isBase&&playerArrow==true)
	{
		_player->frameRender(getMemDC(),playerRc.left, playerRc.top);
	}
	if (isBase&&playerArrow==false)
	{
		_playerBaseLeft->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isLeft)
	{
		_playerLeft->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isRight)
	{
		_playerRight->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isSpace&&playerArrow==true)
	{
		_playerSpace->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isSpace && playerArrow == false)
	{
		_playerLeftSpace->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isSpaceUp&&playerArrow == true)
	{
		_playerSpaceUp->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}
	if (isSpaceUp&&playerArrow == false)
	{
		_playerLeftSpaceUp->frameRender(getMemDC(), playerRc.left , playerRc.top );
	}

	

	//_player->render(getMemDC(), rc.left, rc.top);

	_missile->render(); 
	//RectangleMakeCenter(getMemDC(), playerRc.left, playerRc.top,83 ,_player->getHeight() );
	_hpBar->render();

	
}

void player::draw()
{
	_player->frameRender(getMemDC(), playerRc.left, playerRc.top, 9, 1);


}

RECT player::getPlayerRc()
{
	return playerRc;
}

void player::bulletFire()//캐논볼
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire)continue;

		_bullet[i].isFire = true;
		if (playerArrow == true)
		{
			_bullet[i].x = cosf(_cannon.angle) * (getPlayerRc().right - getPlayerRc().left) + getPlayerRc().right;//방향이 오른쪽일때 오른쪽으로 쏨
		}
		else if (playerArrow == false)
		{
			_bullet[i].x = -cosf(_cannon.angle) * (getPlayerRc().right - getPlayerRc().left) + getPlayerRc().left; //방향이 왼쪽일때 왼쪽으로 쏨
		}

		_bullet[i].y = -sinf(_cannon.angle) * (getPlayerRc().bottom - getPlayerRc().top) + getPlayerRc().bottom - (getPlayerRc().bottom - getPlayerRc().top) ;
		_bullet[i].angle = _cannon.angle;
		break;
	}
}

void player::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire)continue;

		_bullet[i].x += cosf(_bullet[i].angle) * _bullet[i].speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _bullet[i].speed;
	}
}

void player::setPlayerRcTopBottom(int rectTop, int rectBottom)
{
	playerRc.top = rectTop;
	playerRc.bottom = rectBottom;
}

void player::setPlayerRcLeftRight(int rectLeft, int rectRight)
{
	playerRc.left = rectLeft;
	playerRc.right = rectRight;
}

void player::setPlayerRcLeftRightAdd(int rectLeftAdd, int rectRightAdd)
{
	playerRc.left = playerRc.left + rectLeftAdd;
	playerRc.right = playerRc.right + rectRightAdd;

}

void player::setdropbool(bool value)
{
	drop = value;
}

void player::setGravity(int gravity)
{
	playerRc.top += gravity;
	playerRc.bottom += gravity;
}

void player::hitDamage(float damage)
{
	_currentHP -= damage;
}

