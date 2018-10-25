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
	int modelHandle;								// �L�����N�^�[���f���̃n���h��
	int attachMotion;								// ���Ă͂߂����[�V����
	float totalTime;								// ���[�V�����̃g�[�^������
	float angleY;									// ���f���̉�]�
	int attachNum;									// ���[�V�����ԍ�
	const float ROTATE_SPEED = DX_PI_F / 90;		// ���f���̉�]�x��

	float motionBlendTime;							// ���[�V�����̃u�����h����
	float nowPlayTime;								// ���[�V�����̍��̎���
	int preAttach;									// ���O�̃��[�V����
	float preMotionPlayTime;						// ���O�̃��[�V��������

	void Player_PlayAnim(int attach);
	void Player_AnimProcess();

	int animNum;

	int mouseX, mouseY;

	std::vector<int> inputHandle;

	float preAnimSpeed;

	bool noEnd;
	
	std::vector<float> animSpeed;								// �A�j���[�V�����̃X�s�[�h

	VECTOR area;


public:
	Character(std::string fileName);
	~Character();

	void Draw();
	void Process();

	bool GetNoEnd();

	std::vector<float> GetSpeed();
};

