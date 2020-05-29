#pragma once
#include"gameNode.h"
class scene0 : public gameNode
{
public:
	scene0();
	~scene0();

	HRESULT init();
	void release();
	void update();
	void render();
};

