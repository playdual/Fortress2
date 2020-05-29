#pragma once
#include"gameNode.h"
class Bar2 :public gameNode
{
private:

	RECT _rcPower;		// �Ŀ��� ��Ʈ
	RECT _rcHp;
	RECT _rcHp2;
	RECT _rcMove;
	float power;
	float move;
	int playerCurrent;

	bool turn;
	//���α���(��༮���� ������)



public:
	Bar2();
	~Bar2();

	HRESULT init();
	void release();
	void update();
	void render();

	//������ ����
	RECT getRect() { return _rcPower; }
	float getPower() { return power; }
	void setPower(float powergage) { power = powergage; }
	void setRcPowergage(int gage) { _rcPower.right = gage; }
	int getRcpowergage() { return _rcPower.right; }
	void setRcHpgage(int gage) { _rcHp.right -= gage; }
	void setRcHp2gage(int gage) { _rcHp2.right -= gage; }
	void setRcCurrentHpgage(int gage) { _rcHp2.right = gage; }

	int getRcHp2gage() { return _rcHp2.right; }

	void setturn(bool value) { turn = value; }

	float getMove() { return move; }
	void setMove(float movegage) { move = movegage; }
};

