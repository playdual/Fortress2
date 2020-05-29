#pragma once
#include"gameNode.h"
#include"Bar2.h"
#define BULLETMAX 30
struct tagBullet2
{
	image* bulletImage;
	image* exImage;
	RECT rc;

	RECT exrc;
	float x, y;

	float fireX, fireY;
	float radius;
	float angle;
	float speed;
	bool fire;
	bool isFire;
	bool anglebool;
	bool isExp;
	bool isDamege;
	int count;
	int timeCount;
	float gravity;
	int indexCount;
	int index;

};
struct tagCannon2
{
	POINT center;
	POINT cannonEnd;
	int cannon;
	float angle;

};
class missile2 : public gameNode
{
private:
	vector<tagBullet2> _vBullet;
	vector<tagBullet2>::iterator _viBullet;

	tagBullet2 _bullet[BULLETMAX];
	tagCannon2 _cannon;
private:
	RECT WIND;
	float wind;
	float _range;
	float windnum;
	//player2* _player;
	Bar2* _bar2;
	char str[128];
	int _bulletMax;

	int missileCount;
	float ytemp;
	float xtemp;
	float gravit = 10;
	float v_0 = 1;
	float time = 0;



public:

	missile2();
	~missile2();

	HRESULT init(int bulletMax, float range);
	void release();
	void update(RECT playerRc);
	void render();

	//발사
	void fire(float x, float y);
	float getcannonAngle();
	bool anglebool;
	float tempTime = 0.f;
	float pastTime = 0.f;

	float fireError = 0;
	//움직여라
	vector<tagBullet2>& getVBullet() { return _vBullet; }
	void setanglebool(bool value) { anglebool = value; }
	void setVBullet(int i) { _vBullet.erase(_vBullet.begin() + i); }
	void setVBulletbool(int i, bool value) { _vBullet.at(i).anglebool = value; }

	void move();
	void explosion();

	void setPower(float powergage) { _bar2->setPower(powergage); }
	float getPower() { return _bar2->getPower(); }
	void setRcPowergage(int gage) { _bar2->setRcPowergage(gage); }
	int getRcpowergage() { return _bar2->getRcpowergage(); }
	void setRcHpgage(int gage) { _bar2->setRcHpgage(gage); }
	void setRcHp2gage(int gage) { _bar2->setRcHp2gage(gage); }
	int getRcHpgage() { return _bar2->getRcHp2gage(); }
	void setRcCurrentHpgage(int gage) { _bar2->setRcCurrentHpgage(gage); }


	float getMove() { return _bar2->getMove(); }
	void setMove(float movegage) { _bar2->setMove(movegage); }

	void setwind2(float winds) { windnum = winds; }
	
	void setturn(bool value) { _bar2->setturn(value); }


	//void setPlayerMemoryLink(player2* pm) { _player = pm; }

};
