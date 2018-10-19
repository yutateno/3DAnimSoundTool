#pragma once
#include "DxLib.h"


class Character
{
private:
	int modelHandle;
	int attachIndex;
	float totalTime;
	float playTime;
	float angleY;
	const float ROTATE_SPEED = DX_PI_F / 90;


public:
	Character();
	~Character();

	void Draw();
	void Process();
};

