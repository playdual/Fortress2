#pragma once
#include"gameNode.h"
#include"bullet.h"
#include"minion.h"
#include"player.h"

class player;
class enemyManager : public gameNode
{
private:

	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;
	player* _player;

private:

	vEnemy		_vMinion;
	viEnemy		_viMinion;
	bullet* _bullet;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();


	void setMinion();



	vEnemy		getVMinion() { return _vMinion; }
	viEnemy		getViMinion() { return _viMinion; }

	void setplayerMemoryLink(player* player) { _player = player; }
};

