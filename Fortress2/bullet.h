#pragma once
#include"gameNode.h"
#include"Bar.h"

#define BULLETMAX 30
struct tagBullet5
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
struct tagCannon5
{
	POINT center;
	POINT cannonEnd;
	int cannon;
	float angle;

};
class missile : public gameNode
{
private:
	vector<tagBullet5> _vBullet;
	vector<tagBullet5>::iterator _viBullet;

	tagBullet5 _bullet[BULLETMAX];
	tagCannon5 _cannon;
private:
	RECT WIND;
	float wind;
	float _range;
	int windnum;
	//player* _player;
	Bar* _bar;
	char str[128];
	int _bulletMax;
	
	int missileCount;
	float ytemp;
	float xtemp;
	float gravit = 10;
	float v_0 = 1;
	float time=0;



public:
	
	missile();
	~missile();

	HRESULT init(int bulletMax, float range);
	void release();
	void update(RECT playerRc);
	void render();

	//발사
	void fire(float x, float y);
	float getcannonAngle();
	bool anglebool;
	float tempTime=0.f;
	float pastTime = 0.f;

	float fireError=0;
	//움직여라
	vector<tagBullet5>& getVBullet() { return _vBullet; }
	void setanglebool(bool value) { anglebool = value; }
	void setVBullet(int i) { _vBullet.erase(_vBullet.begin()+i); }
	void setVBulletbool(int i, bool value) { _vBullet.at(i).anglebool =  value; }

	void move();          
	void explosion();

	void setPower(float powergage) { _bar->setPower(powergage); }
	float getPower(){return _bar->getPower();}
	void setRcPowergage(int gage) { _bar->setRcPowergage(gage); }
	int getRcpowergage() { return _bar->getRcpowergage(); }
	void setRcHpgage(int gage) { _bar->setRcHpgage(gage); }
	void setRcHp2gage(int gage) { _bar->setRcHp2gage(gage); }
	void setRcCurrentHpgage(int gage) { _bar->setRcCurrentHpgage(gage); }

	int getRcHpgage() { return _bar->getRcHpgage(); }
	
	float getMove() { return _bar->getMove(); }
	void setMove(float movegage) { _bar->setMove(movegage); }

	void setwind(float winds) { windnum = winds; }

	void setturn(bool value) { _bar->setturn(value); }


//	void setPlayerMemoryLink(player* pm) { _player = pm; }

};