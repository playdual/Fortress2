#include "stdafx.h"
#include "Bar2.h"

Bar2::Bar2()
{
}

Bar2::~Bar2()
{
}

HRESULT Bar2::init()
{
	turn = false;

	_rcHp2 = RectMake(WINSIZEX / 2 - 48, WINSIZEY / 2 + 290, 463, 25);
	_rcPower = RectMake(WINSIZEX / 2 - 48, WINSIZEY / 2 + 322, 0, 25);
	_rcMove = RectMake(WINSIZEX / 2 - 48, WINSIZEY / 2 + 355, 463, 25);

	power = 0;
	_rcPower.right = WINSIZEX / 2 - 48;
	move = 463;
	return S_OK;
}

void Bar2::release()
{
}

void Bar2::update()
{
	if (turn == true)
	{
		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
		{
			if (_rcPower.right <= WINSIZEX / 2 - 48 + 463)
			{
				power += 2;
			}
		}
	}

	//최대 power는 463
	_rcPower.right = WINSIZEX / 2 - 48 + power;

	//무브게이지
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_rcMove.right >= WINSIZEX / 2 - 48)
		{
			move -= 3;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_rcMove.right >= WINSIZEX / 2 - 48)
		{
			move -= 3;
		}
	}
	_rcMove.right = WINSIZEX / 2 - 48 + move;
}

void Bar2::render()
{
	if (turn == true)
	{
		HBRUSH Brush, oldBrush;
		Brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = (HBRUSH)SelectObject(getMemDC(), Brush);
		SelectObject(getMemDC(), GetStockObject(NULL_PEN));
		Rectangle(getMemDC(), _rcPower.left, _rcPower.top, _rcPower.right, _rcPower.bottom);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(Brush);


		HBRUSH Brush4, oldBrush4;
		Brush4 = (HBRUSH)CreateSolidBrush(RGB(60, 255, 30));
		oldBrush4 = (HBRUSH)SelectObject(getMemDC(), Brush4);
		Rectangle(getMemDC(), _rcHp2.left, _rcHp2.top, _rcHp2.right, _rcHp2.bottom);
		SelectObject(getMemDC(), oldBrush4);
		DeleteObject(Brush4);

		HBRUSH Brush3, oldBrush3;
		Brush3 = (HBRUSH)CreateSolidBrush(RGB(191, 120, 48));
		oldBrush3 = (HBRUSH)SelectObject(getMemDC(), Brush3);
		Rectangle(getMemDC(), _rcMove.left, _rcMove.top, _rcMove.right, _rcMove.bottom);
		SelectObject(getMemDC(), oldBrush3);
		DeleteObject(Brush3);
	}
}
