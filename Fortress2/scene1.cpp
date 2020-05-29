#include "stdafx.h"
#include "scene1.h"
scene1::scene1()
{
	
}


scene1::~scene1()
{
}

HRESULT scene1::init()
{


	_player = new player;
	_player->init();
	_player2 = new player2;
	_player2->init();
	//미니맵 및 카메라
	IMAGEMANAGER->addImage("카메라", "images/카메라.bmp", (WINSIZEX) / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미니맵", "images/배경.bmp", (WINSIZEX * 2)/ 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다리미니맵", "images/다리.bmp", (WINSIZEX * 2) / 10, WINSIZEY / 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경", "images/배경.bmp", WINSIZEX*2, WINSIZEY,true, RGB(255,0,255));

	mini_rc = RectMakeCenter(100 + (_player->getPlayerRc().left+(_player->getPlayerRc().right- _player->getPlayerRc().left)/2)/10- _camera / 10, 50 + (_player->getPlayerRc().top+(_player->getPlayerRc().bottom- _player->getPlayerRc().top)/2)/10, 10, 10);
	mini_rc2 = RectMakeCenter(100 + (_player2->getplayer2Rc().left+(_player2->getplayer2Rc().right- _player2->getplayer2Rc().left)/2)/10- _camera / 10, 50 + (_player2->getplayer2Rc().top+(_player2->getplayer2Rc().bottom- _player2->getplayer2Rc().top)/2)/10, 10, 10);
	mini_rc2 = RectMakeCenter(100 + (_player2->getplayer2Rc().left+(_player2->getplayer2Rc().right- _player2->getplayer2Rc().left)/2)/10- _camera / 10, 50 + (_player2->getplayer2Rc().top+(_player2->getplayer2Rc().bottom- _player2->getplayer2Rc().top)/2)/10, 10, 10);
	
	arrow = RectMakeCenter((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2), (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2), 52, 98);
	arrowplayer = IMAGEMANAGER->addFrameImage("arrow", "images/화살표.bmp", 105, 98, 2, 1, true, RGB(0, 0, 0));
	arrowplayer2 = IMAGEMANAGER->addFrameImage("arrow2", "images/화살표2.bmp", 83, 98, 2, 1, true, RGB(0, 0, 0));

	Turn = RectMake(WINSIZEX - 64, WINSIZEY - 88, 70, 63);
	_Turn= IMAGEMANAGER->addFrameImage("턴이미지1", "images/1p.bmp", 60, 50, 1, 1, true, RGB(0, 0, 0));
	_Turn2= IMAGEMANAGER->addFrameImage("턴이미지2", "images/2p.bmp", 60, 50, 1, 1, true, RGB(0, 0, 0));


	//총알선택 이미지
	bulletone = RectMake(WINSIZEX/2 - 232, WINSIZEY - 148, 55, 60);
	bullettwo = RectMake(WINSIZEX/2 - 256, WINSIZEY - 79, 58, 62);
	bulletoneOn = IMAGEMANAGER->addFrameImage("총알1온", "images/총알1온.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
	bulletoneOff = IMAGEMANAGER->addFrameImage("총알1오프", "images/총알1오프.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
	bullettwoOn = IMAGEMANAGER->addFrameImage("총알2온", "images/총알2온.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));
	bullettwoOff = IMAGEMANAGER->addFrameImage("총알2오프", "images/총알2오프.bmp", 50, 50, 1, 1, true, RGB(255, 0, 255));



	_rand = new randomFunction;
	wind = 0;
	windbool = false;
	WIND = RectMake(WINSIZEX-89,WINSIZEY/2+218,0,16);


	//바람의 최대 넓이는 -80 ~ 80
	_index = 0;
	_count = 0;
	_camera = 0;
	playerCameratemp = 0;
	player2Cameratemp = 0;

	memoryPlayerLeft = _player->getPlayerRc().left;
	memoryPlayerRight = _player->getPlayerRc().right;

	memoryPlayer2Left = _player2->getplayer2Rc().left;
	memoryPlayer2Right = _player2->getplayer2Rc().right;

	_isLeft = false;
	turn = true;

	_ui=IMAGEMANAGER->addFrameImage("UI", "images/UI.bmp", 1056,196,1,1,true, RGB(255,0,255));
	uirc = RectMake(0, WINSIZEY / 2 + 188, WINSIZEX, 300);
	//IMAGEMANAGER->addImage("다리", "images/다리.bmp", WINSIZEX*2, WINSIZEY,true, RGB(255,0,255));

	_bridge = IMAGEMANAGER->addImage("다리", "images/다리.bmp", WINSIZEX * 2, WINSIZEY-150, true, RGB(255, 0, 255));
	

	playerCurrent = 1;
	return S_OK;
	
}

void scene1::release()
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_player2);
	SAFE_DELETE(_rand);
}

void scene1::update()
{
	if (_player->getPlayerRc().bottom > WINSIZEY - 200 || _player2->getplayer2Rc().bottom > WINSIZEY - 200)
	{
		playerCurrent = 0;
	}

	if (playerCurrent == 0)
	{
		SCENEMANAGER->changeScene("scene0");
	}

	//플레이어 방향가르키기

	arrowcount++;
	arrowplayer->setFrameY(1);
	if (arrowcount % 15 == 0)
	{
		arrowcount = 0;
		arrowindex--;
		if (arrowindex < arrowplayer->getMaxFrameY())
		{
			arrowindex = 2;
		}
		arrowplayer->setFrameX(arrowindex);
	}
	arrowplayer2->setFrameY(1);
	if (arrowcount % 15 == 0)
	{
		arrowcount = 0;
		arrowindex--;
		if (arrowindex < arrowplayer2->getMaxFrameY())
		{
			arrowindex = 2;
		}
		arrowplayer2->setFrameX(arrowindex);
	}
	//방향끝
	if (playerCurrent == 1)
	{
		arrow = RectMakeCenter((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2), _player->getPlayerRc().top -115, 52, 49);
	}
	else if (playerCurrent == 2)
	{
		arrow = RectMakeCenter((_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2), _player2->getplayer2Rc().top -115, 52, 49);
	}

	_player->setGravity(3);
	_player2->setGravity(3);
	
	//바람
	if (playerCurrent == 1&&tempTime<=0.05)
	{
		wind =_rand->getInt(20);
		if (wind <= 10)
		{
			wind = -wind;
		}
		else if (wind > 10 && wind <= 20)
		{
			wind = wind - 10;
		}
	}
	
	_player->setwind(wind);
	_player2->setwind2(wind);
	WIND=RectMake(WINSIZEX - 89, WINSIZEY / 2 + 218, wind*8, 16);

	tempTime += TIMEMANAGER->getElapsedTime();

	//플레이어 1차례
	if (playerCurrent == 1)
	{
		windbool = true;
		windbool = false;
		
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{
			_player->setimagebool(false, false, false, false, true);
			_player->setisShootbool(true);

			_player->setmissilefire(cosf(_player->getcannonangle()) * 1 + 512,
				-sinf(_player->getcannonangle()) * (_player->getPlayerRc().bottom - _player->getPlayerRc().top) + _player->getPlayerRc().bottom);

		//	_camera = -(memoryPlayerLeft + (memoryPlayerRight - memoryPlayerLeft) / 2 - 512);

			//_player->setmissilefire(cosf(_player->getcannonangle()) * 1 + _player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2,
			//	-sinf(_player->getcannonangle()) * (_player->getPlayerRc().bottom - _player->getPlayerRc().top) + _player->getPlayerRc().bottom);
		}

		//캐릭터 프레임이미지 불 값
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2 > 0)
		{
			_player->setimagebool(false, true, false, false,false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_player->setimagebool(true, false, false, false, false);
			_player->setisArrowbool(false);
		}

		//오른쪽
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2 < WINSIZEX)
		{
			_player->setimagebool(false, false, true, false, false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_player->setimagebool(true, false, false, false, false);
			_player->setisArrowbool(true);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player->setPower(0.f);

		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			_player->setimagebool(false, false, false, true, false);
		}
		if (_player->getisShoot())
		{
			shootCount++;
			if (shootCount > 100)
			{

				_player->setimagebool(true, false, false, false, false);
				_player->setisShootbool(false);
				shootCount = 0;
			}
		}
		//맵파괴 픽셀충돌 및 카메라
		auto& bullets = _player->getMissilefunc()->getVBullet();
		for (int i = 0; i < bullets.size(); i++)
		{
			if (turn == true)//총알을 발사하지 않는다면 캐릭터에 따른 고정 카메라를 하지않는다
			{
				//  _player->setPlayerRcLeftRight(_player->getPlayerRc().left + _camera, _player->getPlayerRc().right + _camera);
				playerCameratemp = _camera;
				memoryPlayerLeft = _player->getPlayerRc().left - _camera;
				memoryPlayerRight = _player->getPlayerRc().right - _camera;

				if (_player->getMove() >= 0)
				{
					//카메라
					if (KEYMANAGER->isStayKeyDown(VK_LEFT) && (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) > 0)
					{
						if ((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) <= 173 && _camera < 0)
						{
							_camera = _camera + (WINSIZEX - 173 - (WINSIZEX / 2));
							_player->setPlayerRcLeftRight(462, 562);
							_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);
						}
						else if ((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) >= 0)
						{
							_player->setPlayerRcLeftRightAdd(-2, -2);
						}
					}
					if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) < WINSIZEX)
					{
						if ((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2 >= WINSIZEX - 173) && _camera >= -WINSIZEX + 10)
						{
							_camera = _camera - (WINSIZEX - 173 - (WINSIZEX / 2));
							_player->setPlayerRcLeftRight(462, 562);
							_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);

						}
						else if ((_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) <= WINSIZEX)
						{
							_player->setPlayerRcLeftRightAdd(2, 2);
						}
					}
				}



			}

			//폭발효과
			if (bullets[i].isExp)
			{
				RECT temp;
				if (bullets[i].isDamege == false)
				{
					
						if ((sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
							* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
							- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
							* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 100)
							)
							
						{
							_player->setRcHpgage(30);
							damege = 30;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;

						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 50)
						{
							_player->setRcHpgage(60);
							damege = 60;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;

						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 30)
						{
							_player->setRcHpgage(90);
							damege = 90;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;

						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 10)
						{
							_player->setRcHpgage(120);
							damege = 120;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;

						}
						
						if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 100)
							)
						{

							_player2->setRcHp2gage(30);
							damege = 30;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;


						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 50))
						{

							_player2->setRcHp2gage(60);
							damege = 60;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;


						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 30))
						{

							_player2->setRcHp2gage(90);
							damege = 90;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;


						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 10))
						{

							_player2->setRcHp2gage(120);
							damege = 120;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;

						}
						else
						{
							damege = 0;
							bullets[i].isDamege = true;
						}
					
				}
				if (bullets[i].isDamege == true)
				{
					if (damege > 0)
					{
						damegetxt = true;
					}
					if (pastTime + 3.0f < tempTime)
					{
						bullets[i].isExp = false;
						bullets[i].isDamege = false;
						damegetxt = false;
						pastTime = 0;
						tempTime = 0;
						damege = 0;
					
						_player->setMove(463);
				
						_player2->setMove(463);
						_player->setturn(false);
						_player2->setturn(true);
						/*
						player2CurrentHp = _player2->getRcHpgage();
						_player2->setRcCurrentHpgage(player2CurrentHp);*/
						_camera = player2Cameratemp;
						Cameratemp = 0;
						bulletspeed = 0;
						playerCurrent = 2;
						_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
						_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);
						turn = true;
					}
				}

			}

			if (!bullets[i].isFire)break; //이거 잘봐야함

			turn = false;
			if (bullets[i].isFire == true)
			{
				//총알 쐇을때 총알에 카메라 포커싱
				if (playerCameratemp == 0)
				{
					Cameratemp = -WINSIZEX / 2;
				}

			
					_camera = -(bullets[i].x + playerCameratemp + Cameratemp);
					//_camera = (bullets[i].x + playerCameratemp - WINSIZEX / 2 + Cameratemp);
				
				//_camera = -(memoryPlayerLeft + (memoryPlayerRight - memoryPlayerLeft) / 2 -512);
				//_camera = -(bullets[i].x+playerCameratemp-WINSIZEX/2+Cameratemp);

				//총알이 화면 밖으로 나갔을 때 값 설정
				if (_camera > 0)
				{
					_camera = 0;
				}
				else if (_camera < -WINSIZEX)
				{
					_camera = -WINSIZEX;
				}


				//이전 캐릭터의 위치를 기억해놨다가 그 만큼 카메라값으로 빼줌
				_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
				_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);

				//공이 맵밖으로 빠져나가면 턴넘김
				if ((bullets[i].x <= 5 && _camera == 0) || (bullets[i].x > WINSIZEX&& _camera == -WINSIZEX) || (bullets[i].y > WINSIZEY - 200))
				{
					bullets[i].isExp = false;
					bullets[i].isFire = false;
					pastTime = 0;
					tempTime = 0;
			
					_player->setMove(463);
					_player2->setMove(463);
					_player2->setturn(true);
					_player->setturn(false);
					_camera = player2Cameratemp;
					bulletspeed = 0;
					Cameratemp = 0;
					playerCurrent = 2;
					_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
					_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);
					turn = true;
				}

				//맵파괴
				COLORREF color = GetPixel(_bridge->getMemDC(), _player->getMissilefunc()->getVBullet().at(i).x - _camera, _player->getMissilefunc()->getVBullet().at(i).y);
				if (bullets[i].y >= 10)
				{
					if (!(color == RGB(255, 0, 255)))
					{
						if (!bullets[i].isExp);
						{
							HBRUSH MyBrush, OldBrush;
							MyBrush = CreateSolidBrush(RGB(255, 0, 255));
							OldBrush = (HBRUSH)SelectObject(_bridge->getMemDC(), MyBrush);
							SelectObject(_bridge->getMemDC(), MyBrush);
							SelectObject(_bridge->getMemDC(), GetStockObject(NULL_PEN));
							EllipseMakeCenter(_bridge->getMemDC(), _player->getMissilefunc()->getVBullet().at(i).x - _camera, _player->getMissilefunc()->getVBullet().at(i).y, _player->getMissilefunc()->getVBullet().at(i).radius * 2, _player->getMissilefunc()->getVBullet().at(i).radius * 2);
							DeleteObject(SelectObject(_bridge->getMemDC(), OldBrush));

							pastTime = tempTime;
							bullets[i].isExp = true;
							bullets[i].isFire = false;

						}

					}
				}

			}



		}
		
	}

	if (playerCurrent == 2)
	{
		
		//캐릭터 프레임이미지 불 값
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2 > 0)
		{
			_player2->setimagebool(false, true, false, false,false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_player2->setimagebool(true, false, false, false, false);
			_player2->setisArrowbool(false);
		}

		//오른쪽
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2 < WINSIZEX)
		{
			_player2->setimagebool(false, false, true, false, false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_player2->setimagebool(true, false, false, false, false);
			_player2->setisArrowbool(true);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_player2->setPower(0.f);

		}
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
 			_player2->setimagebool(false, false, false, true, false);
		}
		if (KEYMANAGER->isOnceKeyUp(VK_SPACE))
		{
			_player2->setimagebool(false, false, false, false, true);
			_player2->setisShootbool(true);
			
			_player2->setmissilefire(cosf(_player2->getcannonangle()) * 1 + _player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2,
			-sinf(_player2->getcannonangle()) * (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) + _player2->getplayer2Rc().bottom);

		}
		if (_player2->getisShoot())
		{
			shootCount++;
			if (shootCount > 100)
			{

				_player2->setimagebool(true, false, false, false, false);
				_player2->setisShootbool(false);
				shootCount = 0;
			}
		}
		//맵파괴 픽셀충돌 및 카메라
		auto& bullets = _player2->getMissilefunc()->getVBullet();
		for (int i = 0; i < bullets.size(); i++)
		{
			if (turn == true)//총알을 발사하지 않는다면 캐릭터에 따른 고정 카메라를 하지않는다
			{
				//  _player2->setplayer2RcLeftRight(_player2->getplayer2Rc().left + _camera, _player2->getplayer2Rc().right + _camera);
				player2Cameratemp = _camera;
				memoryPlayer2Left = _player2->getplayer2Rc().left - _camera;
				memoryPlayer2Right = _player2->getplayer2Rc().right - _camera;

				if (_player2->getMove() >= 0)
				{
					//카메라
					if (KEYMANAGER->isStayKeyDown(VK_LEFT) && (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) > 0)
					{
						if ((_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) <= 173 && _camera < 0)
						{
							_camera = _camera + (WINSIZEX - 173 - (WINSIZEX / 2));
							_player2->setplayer2RcLeftRight(462, 562);
							_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight +_camera);

						}
						else if ((_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) >= 0)
						{
							_player2->setplayer2RcLeftRightAdd(-2, -2);
						}
					}
					if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) < WINSIZEX)
					{
						if ((_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2 >= WINSIZEX - 173) && _camera >= -WINSIZEX + 10)
						{
							_camera = _camera - (WINSIZEX - 173 - (WINSIZEX / 2));
							_player2->setplayer2RcLeftRight(462, 562);
							_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);

						}
						else if ((_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) <= WINSIZEX)
						{
							_player2->setplayer2RcLeftRightAdd(2, 2);
						}
					}
				}



			}

			//폭발효과
			if (bullets[i].isExp)
			{
				RECT temp;
				if (bullets[i].isDamege == false)
				{
						if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 100)
							)
						{
							_player2->setRcHp2gage(30);
							damege = 30;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;
						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 50))
						{
							_player2->setRcHp2gage(60);
							damege = 60;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;
						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 30))
						{
							_player2->setRcHp2gage(90);
							damege = 90;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;
						}
						else if ((sqrt((bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							* (bullets[i].x - (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2))
							- (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))
							* (bullets[i].y - (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2))) <= 0))
						{
							_player2->setRcHp2gage(120);
							damege = 120;
							_player2->hitDamage(damege);
							damegeplayer = false;
							bullets[i].isDamege = true;
						}
					
						if (sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
							* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
							- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
							* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2)) <= 100)
							)
						{
							_player->setRcHpgage(30);
							damege = 30;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;
						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 50)
						{
							_player->setRcHpgage(60);
							damege = 60;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;
						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 30)
						{
							_player->setRcHpgage(90);
							damege = 90;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;
						}
						else if
							(sqrt((bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								* (bullets[i].x - (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2))
								- (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))
								* (bullets[i].y - (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2))) <= 10)
						{
							_player->setRcHpgage(120);
							damege = 120;
							_player->hitDamage(damege);
							damegeplayer = true;
							bullets[i].isDamege = true;
						}
						else
						{
							damege = 0;
							bullets[i].isDamege = true;
						}
					//데미지 계산 끝
				
				}
				if (bullets[i].isDamege == true)
				{
					if (damege > 0)
					{
						damegetxt = true;
					}
					if (pastTime + 3.0f < tempTime)
					{
						bullets[i].isExp = false;
						bullets[i].isDamege = false;
						damegetxt = false;
						pastTime = 0;
						tempTime = 0;
						damege = 0;
					/*	_player->setPower(0.f);
						_player2->setPower(0.f);*/
						_player->setMove(463);
						_player2->setMove(463);
						_player->setturn(true);
						_player2->setturn(false);
						_camera = playerCameratemp;
						Cameratemp = 0;
						playerCurrent = 1;
						_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
						_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);
						turn = true;
					}
				}

			}

			if (!bullets[i].isFire)break; //이거 잘봐야함

			turn = false;
			if (bullets[i].isFire == true)
			{
				//총알 쐇을때 총알에 카메라 포커싱
				if (player2Cameratemp == 0)
				{
					Cameratemp = -WINSIZEX / 2;
				}
				_camera = -(bullets[i].x+ player2Cameratemp+Cameratemp);

				                                                                                                                                                                                                //총알이 화면 밖으로 나갔을 때 값 설정
				if (_camera > 0)
				{
					_camera = 0;
				}
				else if (_camera < -WINSIZEX)
				{
					_camera = -WINSIZEX;
				}


				//이전 캐릭터의 위치를 기억해놨다가 그 만큼 카메라값으로 빼줌
				_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
				_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);



				//공이 맵밖으로 빠져나가면 턴넘김
				if ((bullets[i].x <= 5 && _camera == 0) || (bullets[i].x > WINSIZEX&& _camera == -WINSIZEX) || (bullets[i].y > WINSIZEY - 200))
				{
					bullets[i].isExp = false;
					bullets[i].isFire = false;
					pastTime = 0;
					tempTime = 0;
					//_player2->setPower(0.f);
					_player->setMove(463);
					_player2->setMove(463);
					_player->setturn(true);
					_player2->setturn(false);
					_camera = playerCameratemp;
					Cameratemp = 0;
					playerCurrent = 1;
					_player->setPlayerRcLeftRight(memoryPlayerLeft + _camera, memoryPlayerRight + _camera);
					_player2->setplayer2RcLeftRight(memoryPlayer2Left + _camera, memoryPlayer2Right + _camera);
					turn = true;
				}

				//맵파괴
				COLORREF color = GetPixel(_bridge->getMemDC(), _player2->getMissilefunc()->getVBullet().at(i).x - _camera, _player2->getMissilefunc()->getVBullet().at(i).y);
				if (bullets[i].y >= 10)
				{
					if (!(color == RGB(255, 0, 255)))
					{
						if (!bullets[i].isExp);
						{
							HBRUSH MyBrush, OldBrush;
							MyBrush = CreateSolidBrush(RGB(255, 0, 255));
							OldBrush = (HBRUSH)SelectObject(_bridge->getMemDC(), MyBrush);
							SelectObject(_bridge->getMemDC(), MyBrush);
							SelectObject(_bridge->getMemDC(), GetStockObject(NULL_PEN));
							EllipseMakeCenter(_bridge->getMemDC(), _player2->getMissilefunc()->getVBullet().at(i).x - _camera, _player2->getMissilefunc()->getVBullet().at(i).y, _player2->getMissilefunc()->getVBullet().at(i).radius * 2, _player2->getMissilefunc()->getVBullet().at(i).radius * 2);
							DeleteObject(SelectObject(_bridge->getMemDC(), OldBrush));

							pastTime = tempTime;
							bullets[i].isExp = true;
							bullets[i].isFire = false;

						}

					}
				}

			}



		}
		
	}
	//캐릭터 방향이동 픽셀충돌
	for (int i = _player->getPlayerRc().bottom - 10; i < _player->getPlayerRc().bottom + 10; i++)
	{
		COLORREF colorMove = GetPixel(_bridge->getMemDC(), _player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2 - _camera, i);

		if (!(colorMove == RGB(255, 0, 255)))
		{
			_player->setPlayerRcTopBottom(i - (_player->getPlayerRc().bottom - _player->getPlayerRc().top), i);
			_player->setdropbool(false);
			break;
		}
	}

	_player->update();

	//미니맵에 있는 내 위치
	mini_rc = RectMakeCenter(100 + (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) / 10 - _camera / 10, 60 + (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2) / 10, 10, 10);
	
	//플레이어2
	//캐릭터 방향이동 픽셀충돌
	for (int i = _player2->getplayer2Rc().bottom - 10; i < _player2->getplayer2Rc().bottom + 10; i++)
	{
		COLORREF colorMove = GetPixel(_bridge->getMemDC(), _player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2 - _camera, i);

		if (!(colorMove == RGB(255, 0, 255)))
		{
			_player2->setplayer2RcTopBottom(i - (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top), i);
			_player2->setdropbool(false);
			break;
		}
	}

	_player2->update();

	//미니맵에 있는 내 위치
	mini_rc2 = RectMakeCenter(100 + (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) / 10 - _camera / 10, 60 + (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2) / 10, 10, 10);
	tempTime += TIMEMANAGER->getElapsedTime();
}

void scene1::render()
{

	IMAGEMANAGER->render("배경", getMemDC(), _camera, 0);
	IMAGEMANAGER->render("미니맵", getMemDC(), 100, 50);
	IMAGEMANAGER->render("다리미니맵", getMemDC(), 100, 50);
	Rectangle(getMemDC(), mini_rc.left, mini_rc.top, mini_rc.right, mini_rc.bottom);
	Rectangle(getMemDC(), mini_rc2.left, mini_rc2.top, mini_rc2.right, mini_rc2.bottom);
	IMAGEMANAGER->render("카메라", getMemDC(), 100 - _camera / 10, 50);
	IMAGEMANAGER->render("다리", getMemDC(), _camera, 0);

	if (playerCurrent == 1)
	{
		arrowplayer->frameRender(getMemDC(), arrow.left, arrow.top);
	}
	else if (playerCurrent == 2)
	{
		arrowplayer2->frameRender(getMemDC(), arrow.left, arrow.top);
	}
	/* 남은시간 구현시 사용할 시간 기능
	tempTime += TIMEMANAGER->getElapsedTime();
	pastTime =tempTime;
	*/
	char str[25];
	sprintf_s(str, "카메라 : %f", _camera);
	TextOut(getMemDC(), WINSIZEX-200, 50, str, strlen(str));

	//char strtime[25];
	//sprintf_s(strtime, "시간 : %f", tempTime);
	//TextOut(getMemDC(), 600, 200, strtime, strlen(strtime));

	//char strpasttime[25];
	//sprintf_s(strpasttime, "과거시간 : %f", pastTime);
	//TextOut(getMemDC(), 600, 250, strpasttime, strlen(strpasttime));

	

	if (damegeplayer == true)//1번플레이어 대미지 받음(캐릭터위 빨간색 숫자 표시)
	{
		if (damegetxt)
		{
			SetTextColor(getMemDC(), RGB(255, 0, 0));
			sprintf_s(Damege, "- %d", damege);
			TextOut(getMemDC(), (_player->getPlayerRc().left + (_player->getPlayerRc().right - _player->getPlayerRc().left) / 2) - 15, (_player->getPlayerRc().top + (_player->getPlayerRc().bottom - _player->getPlayerRc().top) / 2) - 90, Damege, strlen(Damege));
		}
	}
	if (damegeplayer == false)//2번플레이어 대미지 받음
	{
		if (damegetxt)
		{
			SetTextColor(getMemDC(), RGB(255, 0, 0));
			sprintf_s(Damege, "- %d", damege);
			TextOut(getMemDC(), (_player2->getplayer2Rc().left + (_player2->getplayer2Rc().right - _player2->getplayer2Rc().left) / 2) - 15, (_player2->getplayer2Rc().top + (_player2->getplayer2Rc().bottom - _player2->getplayer2Rc().top) / 2) - 90, Damege, strlen(Damege));

		}
	}
	
	

 


	//Rectangle(getMemDC(), arrow.left, arrow.top, arrow.right, arrow.bottom);
	_ui->frameRender(getMemDC(), uirc.left, uirc.top);
	_player->render();
	_player2->render();
	
	//sprintf_s(str, "WIND :  %.1f", wind);
	//TextOut(getMemDC(), 500, 100, str, strlen(str));
	
	//바람게이지
	HBRUSH MyBrush7, OldBrush7;
	MyBrush7 = CreateSolidBrush(RGB(0, 220, 50));
	OldBrush7 = (HBRUSH)SelectObject(getMemDC(), MyBrush7);
	SelectObject(getMemDC(), MyBrush7);
	SelectObject(getMemDC(), GetStockObject(NULL_PEN));
	Rectangle(getMemDC(), WIND.left, WIND.top, WIND.right, WIND.bottom);
	DeleteObject(SelectObject(_bridge->getMemDC(), OldBrush7));

	
	
	if (playerCurrent == 1)
	{
		_Turn->frameRender(getMemDC(), Turn.left, Turn.top);
	}
	else if (playerCurrent == 2)
	{
		_Turn2->frameRender(getMemDC(), Turn.left, Turn.top);
	}
	
	//Rectangle(getMemDC(), Turn.left, Turn.top, Turn.right, Turn.bottom);
	//Rectangle(getMemDC(), wind.left, wind.top, wind.right, wind.bottom);

	/*Rectangle(getMemDC(), bulletone.left, bulletone.top, bulletone.right, bulletone.bottom);
	Rectangle(getMemDC(), bullettwo.left, bullettwo.top, bullettwo.right, bullettwo.bottom);*/

	bulletoneOn->frameRender(getMemDC(), bulletone.left, bulletone.top);
	bullettwoOff->frameRender(getMemDC(), bullettwo.left, bullettwo.top);
}


