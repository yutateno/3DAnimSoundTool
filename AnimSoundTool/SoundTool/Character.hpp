#pragma once
#include "DxLib.h"
#include <math.h>
#include "InputMouse.hpp"
#include "InputKey.hpp"
#include <string>
#include <vector>


class Character
{
private:
	int modelHandle;								// キャラクターモデルのハンドル
	int attachMotion;								// あてはめたモーション
	float totalTime;								// モーションのトータル時間
	float angleY;									// モデルの回転具合
	int attachNum;									// モーション番号
	const float ROTATE_SPEED = DX_PI_F / 90;		// モデルの回転度数

	float motionBlendTime;							// モーションのブレンド時間
	float nowPlayTime;								// モーションの今の時間
	int preAttach;									// 直前のモーション
	float preMotionPlayTime;						// 直前のモーション時間

	void Player_PlayAnim(int attach);
	void Player_AnimProcess();

	int animNum;

	int mouseX, mouseY;

	std::vector<int> inputHandle;

	float preAnimSpeed;

	bool noEnd;

	std::vector<float> animSpeed;								// アニメーションのスピード

	VECTOR area;

	std::vector<float> soundArea;

	void SoundProcess();

	void SoundDraw();

	std::vector<int> soundPlay;

	std::vector<std::string> soundName;

	int soundNum;

	std::vector<int> soundNumber;


public:
	Character(std::string fileName, int soundNum);
	~Character();

	void Draw();
	void Process();

	bool GetNoEnd();

	void SetSpeed(std::vector<float> speed);
	std::vector<float> GetSoundArea();
	void SetSound(std::vector<int> sound);
	void SetSoundName(std::vector<std::string> str);
	std::vector<int> GetSoundNumber();
	std::vector<std::string> GetSoundName();
};

