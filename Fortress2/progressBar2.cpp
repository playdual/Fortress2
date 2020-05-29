#include "stdafx.h"
#include "progressBar2.h"
progressBar2::progressBar2()
{
}


progressBar2::~progressBar2()
{
}

HRESULT progressBar2::init(char* frontImage, char* backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBar2Front = new image;
	_progressBar2Front->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBar2Back = new image;
	_progressBar2Back->init(backImage, x, y, width, height, true, RGB(255, 0, 255));


	_width = _progressBar2Front->getWidth();

	return S_OK;
}

void progressBar2::release()
{
	SAFE_DELETE(_progressBar2Front);
	SAFE_DELETE(_progressBar2Back);
}

void progressBar2::update()
{
	_rcProgress = RectMakeCenter(_x + _progressBar2Back->getWidth() / 2,
		_y + _progressBar2Back->getHeight() / 2,
		_progressBar2Back->getWidth(), _progressBar2Back->getHeight());
}

void progressBar2::render()
{
	_progressBar2Back->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressBar2Back->getWidth(), _progressBar2Back->getHeight());

	_progressBar2Front->render(getMemDC(), _rcProgress.left, _y, 0, 0, _width, _progressBar2Back->getHeight());

}
void progressBar2::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBar2Back->getWidth();
}
