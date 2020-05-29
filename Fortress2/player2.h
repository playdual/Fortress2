#pragma once
#include"gameNode.h"
#include"bullet2.h"
#include"progressBar2.h"
#define player2SPEED 2
class player2 :public gameNode
{
	struct tagBullet1
	{
		float x, y;
		float speed;
		float angle;
		float radius;
		float gravity;
		bool isFire;

		RECT rc;
	};

	struct tagCannon1
	{
		POINT center;
		POINT cannonEnd;
		int cannon;
		float angle;
	};
private:


	image* _player2;
	image* _player2BaseLeft;
	image* _player2Left;
	image* _player2Right;
	image* _player2Space;
	image* _player2SpaceUp;
	image* _player2LeftSpace;
	image* _player2LeftSpaceUp;
	image* _player2Ui;

	missile2* _missile2;
	RECT rc;
	RECT player2Rc;

	tagBullet1 _bullet[BULLETMAX];
	tagCannon1 _cannon;

	bool isisFire;
	bool isBase;
	bool isBaseLeft;
	bool isLeft;
	bool isRight;
	bool isSpace;
	bool isLeftSpace;
	bool isSpaceUp;
	bool isLeftSpaceUp;

	bool isShoot;
	bool drop;

	bool player2Arrow;

	int baseCount;
	int baseIndex;
	int leftCount;
	int leftIndex;
	int rightCount;
	int rightIndex;
	int spaceCount;
	int spaceIndex;
	int spaceUpCount;
	int spaceUpIndex;

	int shootCount;


	//프로그레스바 
	progressBar2* _hpBar;
	float _maxHP;
	float _currentHP;

public:
	player2();
	~player2();



	HRESULT init();
	void release();
	void update();
	void render();

	//미슬 삭제
	void removeMissile(int arrNum);
	//충돌함수
	//void collision();
	//피깎는 함수
	void hitDamage(float damage);
	void draw();

	//뉴클리어 가져오기
	//nuclear* getMissile() { return _nuclear; }
	missile2* getMissilefunc() { return _missile2; }
	//로켓 이미지 가져오기
	image* getplayer2Image() { return _player2; }
	RECT getplayer2Rc();
	void setPlayer2Rc(RECT rect) { player2Rc = rect; }

	void bulletFire();
	void bulletMove();
	void setVBullet(int i) { _missile2->setVBullet(i); }

	void setplayer2RcTopBottom(int rectTop, int rectBottom);
	void setplayer2RcLeftRight(int rectLeft, int rectRight);
	void setplayer2RcLeftRightAdd(int rectLeftAdd, int rectRightAdd);
	void setdropbool(bool value);
	void setGravity(int gravity);
	bool getplayer2Arrow() { return player2Arrow; }
	float getCannonAngle() { return _cannon.angle; }
	tagBullet1 getbullet(int i) { return _bullet[i]; }

	void setisisfire(bool value) { isisFire = value; }
	//void setEnemyMemoryLink(enemyManager* em) { _em = em; }
//	void setScene1MemoryLink(scene1* sc) { _sc = sc; }

	void setPower(float powergage) { _missile2->setPower(powergage); }
	float getPower() { return _missile2->getPower(); }
	void setRcPowergage(int gage) { _missile2->setRcPowergage(gage); }
	int getRcpowergage() { return _missile2->getRcpowergage(); }

	float getMove() { return _missile2->getMove(); }
	void setMove(float movegage) { _missile2->setMove(movegage); }


	void setmissilefire(float x, float y) { _missile2->fire(x, y); }
	float getcannonangle() { return _missile2->getcannonAngle(); }
	void setRcHp2gage(int gage) { _missile2->setRcHp2gage(gage); }
	int getRcHpgage() { return _missile2->getRcHpgage(); }
	void setRcCurrentHpgage(int gage) { _missile2->setRcCurrentHpgage(gage); }
	void setturn(bool value) { _missile2->setturn(value); }


	void setimagebool(bool base, bool left, bool right, bool space, bool spaceup)
	{
		isBase = base, isLeft = left; isRight = right, isSpace = space, isSpaceUp = spaceup;
	}
	void setisShootbool(bool shoot)
	{
		isShoot = shoot;
	}
	void setisArrowbool(bool Arrow)
	{
		player2Arrow = Arrow;
	}
	bool getisShoot() { return isShoot; }

	void setwind2(float winds) { _missile2->setwind2(winds); }

};

