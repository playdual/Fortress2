#pragma once
#include"gameNode.h"
class progressBar :public gameNode
{
private:

	RECT _rcProgress;		// 체력바 렉트
	RECT _rcProgress2;		// 체력바 렉트
	int _x, _y;
	int _x2, _y2;
	int _width;				//가로길이(요녀석으로 조정함)
	int _width2;				//가로길이(요녀석으로 조정함)

	image* _progressBarFront;		//체력바 앞이미지
	image* _progressBarBack;		//체력바 뒤이미지
	image* _progressBarFront2;		//체력바 앞이미지
	image* _progressBarBack2;		//체력바 뒤이미지

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
	//게이지 셋팅
	void setGauge(float currentGauge, float maxGauge);
	void setGauge2(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect() { return _rcProgress; }
};

