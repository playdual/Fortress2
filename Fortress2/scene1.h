#pragma once
#include"gameNode.h"
#include"player.h"
#include"player2.h"
#include"randomFunction.h"

class scene1 : public gameNode
{
private:


	RECT uirc;
	RECT WIND;
	RECT Turn;

	RECT bulletone;
	RECT bullettwo;

	image* bulletoneOn;
	image* bulletoneOff;
	image* bullettwoOn;
	image* bullettwoOff;


	image* _Turn;
	image* _Turn2;
	image* arrowplayer;
	image* arrowplayer2;
	image* _bridge;
	image* _ui;
	randomFunction* _rand;
	player* _player;
	player2* _player2;
	int playerCurrent;
	//미니맵, 카메라 관련
	int _index;
	int _count;
	int arrowcount;
	int arrowindex;

	int playerCurrentHp;
	int player2CurrentHp;


	float wind;
	float _camera;
	float playerCameratemp;
	float player2Cameratemp;
	float memoryPlayerLeft;
	float memoryPlayerRight;
	float memoryPlayer2Left;
	float memoryPlayer2Right;

	float bulletspeed;

	int shootCount=0;
	int Cameratemp;
	bool _isLeft;
	bool turn;
	bool damegetxt;
	bool windbool;
	bool damegeplayer;

	char Damege[25];
	int damege;

	RECT mini_rc;
	RECT mini_rc2;
	RECT arrow;



	float tempTime = 0.f;
	float pastTime = 0.f;
	float fireError = 0;
public:
	scene1();
	~scene1();

	HRESULT init();
	void release();
	void update();
	void render();

	void setplusCamera(int camera) { _camera +=camera; }
	void setminusCamera(int camera) { _camera -= camera; }
	int getCamera() { return _camera; }
	void setPlayerMemoryLink(player* player) { _player = player; }

	void setFireError(float i) { fireError += i; }

};

