#pragma once
#include"gameNode.h"
class progressBar2 :public gameNode
{
private:

	RECT _rcProgress;		// ü�¹� ��Ʈ
	int _x, _y;
	int _width;				//���α���(��༮���� ������)

	image* _progressBar2Front;		//ü�¹� ���̹���
	image* _progressBar2Back;		//ü�¹� ���̹���


public:
	progressBar2();
	~progressBar2();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();
	//������ ����
	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

