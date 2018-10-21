#include "Character.hpp"

// �g���A�j���[�V�����Ǘ�
void Character::Player_PlayAnim(int attach)
{
	// ���̃��[�V�������Ⴄ���̂�������
	if (attachNum != attach)
	{
		// ���O�̃��[�V�������L����������f�^�b�`����
		if (preAttach != -1 && motionBlendTime < 1.0f)
		{
			MV1DetachAnim(modelHandle, preAttach);
			preAttach = -1;
		}
		// ���̃��[�V����������
		preAttach = attachMotion;
		preMotionPlayTime = nowPlayTime;

		// ���������̃��[�V�����ԍ��ɓ����
		attachNum = attach;

		// �V���Ɏw��̃��[�V���������f���ɃA�^�b�`����
		attachMotion = MV1AttachAnim(modelHandle, attachNum, -1, false);

		// ���쎞�Ԃ�����������
		nowPlayTime = 0.0f;

		// �u�����h���͒��O�̃��[�V�������L���ł͂Ȃ��ꍇ�͂P�D�O��( �Đ����̃��[�V�����P���P�O�O���̏�� )�ɂ���
		if (preMotionPlayTime == -1)
		{
			motionBlendTime = 1.0f;
		}
		else
		{
			motionBlendTime = 0.0f;
		}
	}
}

// �S�ẴA�j���[�V�����̊Ǘ�
void Character::Player_AnimProcess()
{
	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (motionBlendTime < 1.0)
	{
		motionBlendTime += 0.075f;
		if (motionBlendTime >= 1.0f)
		{
			motionBlendTime = 1.0f;
		}
	}

	// �Đ����Ă��錻�݂̃��[�V�����̏���
	if (attachMotion != -1)
	{
		// ���[�V�����̑����Ԃ��擾
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachMotion);

		// �Đ����Ԃ�i�߂�
		nowPlayTime += animSpeed;


		// �Đ����Ԃ������Ԃɓ��B���Ă����烋�[�v������
		if (nowPlayTime >= totalTime)
		{
			nowPlayTime = fmodf(nowPlayTime, totalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, attachMotion, nowPlayTime);

		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, attachMotion, motionBlendTime);
	}

	// �Đ����Ă��钼�O�̃��[�V�����̏���
	if (preAttach != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, preAttach);

		// �Đ����Ԃ�i�߂�
		preMotionPlayTime += animSpeed;

		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (preMotionPlayTime > totalTime)
		{
			preMotionPlayTime = fmodf(preMotionPlayTime, totalTime);
		}

		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(modelHandle, preAttach, preMotionPlayTime);

		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(modelHandle, preAttach, (1.0f - motionBlendTime));
	}
}


Character::Character(std::string fileName)
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel(fileName.c_str());

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 1000.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 170, -200), VGet(0.0f, 120.0f, 0.0f));

	attachNum = 1;

	// �R�c���f����0�Ԗڂ̃A�j���[�V�������A�^�b�`����
	attachMotion = MV1AttachAnim(modelHandle, attachNum, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachMotion);


	angleY = 0.0f;

	animSpeed = 0.3f;
	preAnimSpeed = animSpeed;
	nowPlayTime = 0.0f;
	motionBlendTime = 0.0f;
	preAttach = -1;
	preMotionPlayTime = 0.0f;

	animNum = MV1GetAnimNum(modelHandle);

	GetMousePoint(&mouseX, &mouseY);

	inputHandle = MakeKeyInput(10, FALSE, TRUE, TRUE);      // ���p�p�������̓n���h��

	noEnd = true;
}


Character::~Character()
{
	MV1DeleteModel(modelHandle);
}

void Character::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);


	// ���[�V�����ԍ��Ɩ��O
	for (int i = 0; i != animNum; ++i)
	{
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 255, 255), true);
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(0, 255, 255), false);
		DrawFormatString(8, i * 24, GetColor(0, 0, 0), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		if (mouseX >= 0 && mouseX <= 200 && mouseY > i * 24 && mouseY < i * 24 + 24)
		{
			DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 0, 0), false);
			DrawFormatString(8, i * 24, GetColor(125, 125, 125), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		}
	}

	
	// ���[�V�����̓����̃o�[
	DrawLine(300, 50, 980, 50, GetColor(255, 255, 255));
	DrawBox(290 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680)
		, 30, 310 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680), 70, GetColor(0, 125, 125), true);


	// ���[�V�������x�̊m�F
	DrawBox(1050, 38, 1050 + 200, 62, GetColor(255, 255, 255), true);
	DrawBox(1050, 38, 1050 + 200, 62, GetColor(0, 255, 255), false);
	if (animSpeed != 0.0f)
	{
		DrawFormatString(1050, 38, GetColor(0, 0, 0), "Speed : %f", animSpeed);
	}
	else
	{
		DrawFormatString(1050, 38, GetColor(0, 0, 0), "Speed : %f", preAnimSpeed);
	}


	// ���[�V�������x�̕ύX
	DrawBox(1050, 70, 1050 + 200, 94, GetColor(0, 0, 0), true);
	DrawBox(1050, 70, 1050 + 200, 94, GetColor(0, 255, 255), false);
	if (CheckKeyInput(inputHandle) == 0)
	{
		DrawKeyInputString(1050, 70, inputHandle);   // ���͓r���̕������`��
	}

	
	// ���[�V�����X�g�b�v����
	DrawFormatString(20, 600, GetColor(255, 255, 255), "�X�y�[�X�L�[�Ń��[�V�����X�g�b�v");


	// ���f���M��I��
	DrawBox(1200, 700, 1250, 750, GetColor(255, 0, 0), true);
	DrawBox(1200, 700, 1250, 750, GetColor(125, 125, 125), false);
	DrawCircle(1225, 725, 10, GetColor(0, 0, 0), false);
	DrawLine(1225, 710, 1225, 720, GetColor(0, 0, 0));
}

void Character::Process()
{
	GetMousePoint(&mouseX, &mouseY);

	for (int i = 0; i != animNum; ++i)
	{
		if (mouseX >= 0 && mouseX <= 200 && mouseY > i * 24 && mouseY < i * 24 + 24
			&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
		{
			Player_PlayAnim(i);
		}
	}

	if (mouseX >= 1050 && mouseX <= 1050 + 200 && mouseY > 70 && mouseY < 94
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		SetActiveKeyInput(inputHandle);   // ���̓n���h�����A�N�e�B�u��
	}

	if (CheckKeyInput(inputHandle) == 1)
	{
		animSpeed = GetKeyInputNumberToFloat(inputHandle);   // ���͓r���̕������`��
	}

	if (KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		if (animSpeed != 0.0f)
		{
			preAnimSpeed = animSpeed;
			animSpeed = 0.0f;
		}
		else
		{
			animSpeed = preAnimSpeed;
		}
	}

	DrawLine(300, 50, 980, 50, GetColor(255, 255, 255));
	DrawBox(290 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680)
		, 30, 310 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680), 70, GetColor(0, 125, 125), true);

	if (mouseX >= 300 && mouseX <= 980 && mouseY >= 20 && mouseY <= 80
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) >= 1)
	{
		nowPlayTime = ((mouseX - 300) / 680.0f) * MV1GetAttachAnimTotalTime(modelHandle, attachMotion);
	}

	Player_AnimProcess();

	if (KeyData::Get(KEY_INPUT_LEFT) > 0)
	{
		angleY -= ROTATE_SPEED;
	}

	if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
	{
		angleY += ROTATE_SPEED;
	}

	if (mouseX >= 1200 && mouseX <= 1250 && mouseY >= 700 && mouseY <= 750
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		noEnd = false;
	}

	//�������̉�]�p�x���Z�b�g
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY, 0.0f));
}

bool Character::GetNoEnd()
{
	return noEnd;
}
