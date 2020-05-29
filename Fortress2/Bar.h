#pragma once
#include"gameNode.h"
class Bar :public gameNode
{
private:

	RECT _rcPower;		// �Ŀ��� ��Ʈ
	RECT _rcHp;
	RECT _rcHp2;
	RECT _rcMove;
	float power1;
	float move;
	
	bool turn;

	int playerCurrent;
	//���α���(��༮���� ������)



public:
	Bar();
	~Bar();

	HRESULT init();
	void release();
	void update();
	void render();

	//������ ����
	RECT getRect() { return _rcPower; }
	float getPower() { return power1; }
	void setPower(float powergage) { power1 = powergage; }
	void setRcPowergage(int gage) { _rcPower.right = gage; }
	int getRcpowergage() { return _rcPower.right; }
	void setRcHpgage(int gage) { _rcHp.right -= gage; }
	void setRcHp2gage(int gage) { _rcHp2.right -= gage; }

	void setRcCurrentHpgage(int gage) { _rcHp.right = gage; }
	int getRcHpgage() { return _rcHp.right; }

	void setturn(bool value) { turn = value; }

	float getMove() { return move; }
	void setMove(float movegage) { move = movegage; }
};

