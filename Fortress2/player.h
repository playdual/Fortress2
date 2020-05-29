#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"progressBar.h"

#define PLAYERSPEED 2
#define BULLETMAX 30
class player:public gameNode
{
struct tagBullet4
{
	float x, y;
	float speed;
	float angle;
	float radius;
	float gravity;
	bool isFire;

	RECT rc;
};

struct tagCannon4
{
	POINT center;
	POINT cannonEnd;
	int cannon;
	float angle;
};
private:
	

	image* _player;
	image* _playerBaseLeft;
	image* _playerLeft;
	image* _playerRight;
	image* _playerSpace;
	image* _playerSpaceUp;
	image* _playerLeftSpace;
	image* _playerLeftSpaceUp;
	image* _playerUi;

	missile* _missile;
	RECT rc;
	RECT playerRc;

	tagBullet4 _bullet[BULLETMAX];
	tagCannon4 _cannon;

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

	bool playerArrow;

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
	progressBar* _hpBar;
	float _maxHP;
	float _currentHP;

public:
	player();
	~player();



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
	missile* getMissilefunc() { return _missile; }
	//로켓 이미지 가져오기
	image* getplayerImage() { return _player; }
	RECT getPlayerRc();
	void setPlayerRc(RECT rect) { playerRc=rect; }

	void bulletFire();
	void bulletMove();
	void setVBullet(int i) {_missile->setVBullet(i) ;}

	void setPlayerRcTopBottom(int rectTop, int rectBottom);
	void setPlayerRcLeftRight(int rectLeft, int rectRight);
	void setPlayerRcLeftRightAdd(int rectLeftAdd, int rectRightAdd);
	void setdropbool(bool value);
	void setGravity(int gravity);
	bool getPlayerArrow() { return playerArrow; }
	float getCannonAngle() { return _cannon.angle; }
	tagBullet4 getbullet(int i) { return _bullet[i]; }

	void setisisfire(bool value) { isisFire = value; }
	//void setEnemyMemoryLink(enemyManager* em) { _em = em; }
//	void setScene1MemoryLink(scene1* sc) { _sc = sc; }

	void setPower(float powergage) {_missile->setPower(powergage); }
	float getPower() { return _missile->getPower(); }
	void setRcPowergage(int gage) { _missile->setRcPowergage(gage); }
	int getRcpowergage() { return _missile->getRcpowergage(); }

	float getMove() { return _missile->getMove(); }
	void setMove(float movegage) { _missile->setMove(movegage); }


	void setmissilefire(float x, float y) { _missile->fire(x, y); }
	float getcannonangle() { return _missile->getcannonAngle(); }
	void setRcHpgage(int gage) { _missile->setRcHpgage(gage); }
	int getRcHpgage() { return _missile->getRcHpgage(); }
	void setRcCurrentHpgage(int gage) { _missile->setRcCurrentHpgage(gage); }

	void setturn(bool value) { _missile->setturn(value); }


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
		playerArrow = Arrow;
	}
	bool getisShoot() { return isShoot; }

	void setwind(float winds) { _missile->setwind(winds); }


};

