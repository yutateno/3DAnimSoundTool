#include "Character.hpp"



Character::Character()
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("model\\CLPH_motionALL.mv1");

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 1000.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 170, -200), VGet(0.0f, 120.0f, 0.0f));

	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	attachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);

	// �Đ����Ԃ̏�����
	playTime = 0.0f;

	angleY = 0.0f;
}


Character::~Character()
{
	MV1DeleteModel(modelHandle);
}

void Character::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);
}

void Character::Process()
{
	// �Đ����Ԃ�i�߂�
	playTime += 0.2f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (playTime >= totalTime)
	{
		playTime = 0.0f;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

	if (CheckHitKey(KEY_INPUT_LEFT) > 0)
	{
		angleY -= ROTATE_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) > 0) 
	{
		angleY += ROTATE_SPEED;
	}

	//�������̉�]�p�x���Z�b�g
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY, 0.0f));
}
