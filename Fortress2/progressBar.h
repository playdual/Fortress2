#pragma once
#include"gameNode.h"
class progressBar :public gameNode
{
private:

	RECT _rcProgress;		// ü�¹� ��Ʈ
	RECT _rcProgress2;		// ü�¹� ��Ʈ
	int _x, _y;
	int _x2, _y2;
	int _width;				//���α���(��༮���� ������)
	int _width2;				//���α���(��༮���� ������)

	image* _progressBarFront;		//ü�¹� ���̹���
	image* _progressBarBack;		//ü�¹� ���̹���
	image* _progressBarFront2;		//ü�¹� ���̹���
	image* _progressBarBack2;		//ü�¹� ���̹���

public:
	progressBar();
	~progressBar();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	HRESULT init2(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void update2();
	void render();
	void render2();
	//������ ����
	void setGauge(float currentGauge, float maxGauge);
	void setGauge2(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

