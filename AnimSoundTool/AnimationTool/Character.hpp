#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include <string>


class Character
{
private:
	int modelHandle;
	int attachMotion;
	float totalTime;
	float angleY;
	int attachNum;
	const float ROTATE_SPEED = DX_PI_F / 90;

	float motionBlendTime;
	float nowPlayTime;
	float animSpeed;
	int preAttach;
	float preMotionPlayTime;

	void Player_PlayAnim(int attach);
	void Player_AnimProcess();

	int animNum;

	int mouseX, mouseY;

	int inputHandle;

	float preAnimSpeed;

	bool noEnd;


public:
	Character(std::string fileName);
	~Character();

	void Draw();
	void Process();

	bool GetNoEnd();
};

