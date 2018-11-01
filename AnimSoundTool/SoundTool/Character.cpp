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
		nowPlayTime += animSpeed[attachNum];


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
		preMotionPlayTime += 0.3f;

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


void Character::SoundProcess()
{
	for (int i = 0; i != soundNum; ++i)
	{
		if (mouseX > 200 && mouseX < 400 && mouseY > i * 24 && mouseY < i * 24 + 24
			&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
		{
			soundNumber[attachNum] = i;
		}
	}

	int tempA = static_cast<int>(nowPlayTime);				// �����Ë��B����v�C���B
	int tempB = static_cast<int>(soundArea[attachNum]);		// �����Ë��B����v�C���B

	if (soundNumber[attachNum] != -1 && tempA == tempB && animSpeed[attachNum] != 0.0f)
	{
		PlaySoundMem(soundPlay[soundNumber[attachNum]], DX_PLAYTYPE_BACK, true);
	}
}

void Character::SoundDraw()
{
	// ���[�V�����ԍ��Ɩ��O
	for (int i = 0; i != soundNum; ++i)
	{
		DrawBox(200, i * 24, 400, i * 24 + 24, GetColor(255, 255, 255), true);
		DrawBox(200, i * 24, 400, i * 24 + 24, GetColor(0, 255, 255), false);
		DrawFormatString(208, i * 24, GetColor(0, 0, 0), "%d : %s", i, soundName[i].c_str());
		if (mouseX > 200 && mouseX < 400 && mouseY > i * 24 && mouseY < i * 24 + 24)
		{
			DrawBox(200, i * 24, 400, i * 24 + 24, GetColor(255, 0, 0), false);
			DrawFormatString(208, i * 24, GetColor(125, 125, 125), "%d : %s", i, soundName[i].c_str());
		}
	}
	DrawBox(200, (soundNum + 1) * 24, 400, (soundNum + 1) * 24 + 24, GetColor(255, 255, 255), true);
	DrawBox(200, (soundNum + 1) * 24, 400, (soundNum + 1) * 24 + 24, GetColor(0, 255, 255), false);
	if (soundNumber[attachNum] == -1)
	{
		DrawFormatString(208, (soundNum + 1) * 24, GetColor(0, 0, 0), "NONE");
	}
	else
	{
		DrawFormatString(208, (soundNum + 1) * 24, GetColor(0, 0, 0), "Now : %s", soundName[soundNumber[attachNum]].c_str());
	}
}

Character::Character(std::string fileName, int soundNum)
{
	// �R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel(fileName.c_str());

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 1000.0f);

	area = VGet(0, 170, -200);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(area, VGet(0.0f, 120.0f, 0.0f));

	attachNum = 1;

	// �R�c���f����0�Ԗڂ̃A�j���[�V�������A�^�b�`����
	attachMotion = MV1AttachAnim(modelHandle, attachNum, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachMotion);


	angleY = 0.0f;

	nowPlayTime = 0.0f;
	motionBlendTime = 0.0f;
	preAttach = -1;
	preMotionPlayTime = 0.0f;

	animNum = MV1GetAnimNum(modelHandle);

	animSpeed.resize(animNum);
	for (int i = 0; i != animSpeed.size(); ++i)
	{
		animSpeed[i] = 0.3f;
	}
	preAnimSpeed = animSpeed[attachNum];

	GetMousePoint(&mouseX, &mouseY);


	inputHandle.resize(animNum);
	for (int i = 0; i != inputHandle.size(); ++i)
	{
		inputHandle[i] = MakeKeyInput(5, FALSE, TRUE, TRUE);      // ���p�p�������̓n���h��
	}

	
	soundArea.resize(animNum);
	for (int i = 0; i != soundArea.size(); ++i)
	{
		soundArea[i] = 0.0f;
	}

	this->soundNum = soundNum;

	soundPlay.resize(soundNum);
	for (int i = 0; i != soundNum; ++i)
	{
		soundPlay[i] = -1;
	}

	soundNumber.resize(animNum);
	for (int i = 0; i != animNum; ++i)
	{
		soundNumber[i] = -1;
	}

	soundName.resize(soundNum);
	for (int i = 0; i != soundNum; ++i)
	{
		soundName[i] = "";
	}

	noEnd = true;
}


Character::~Character()
{
	for (int i = 0; i != inputHandle.size(); ++i)
	{
		DeleteKeyInput(inputHandle[i]);
	}
	inputHandle.clear();
	inputHandle.shrink_to_fit();

	animSpeed.clear();
	animSpeed.shrink_to_fit();

	soundArea.clear();
	soundArea.shrink_to_fit();

	soundPlay.clear();
	soundPlay.shrink_to_fit();

	soundNumber.clear();
	soundNumber.shrink_to_fit();

	soundName.clear();
	soundName.shrink_to_fit();

	MV1DeleteModel(modelHandle);
}

void Character::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(modelHandle);

	SoundDraw();

	// ���[�V�����ԍ��Ɩ��O
	for (int i = 0; i != animNum; ++i)
	{
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 255, 255), true);
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(0, 255, 255), false);
		DrawFormatString(8, i * 24, GetColor(0, 0, 0), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		if (mouseX > 0 && mouseX < 200 && mouseY > i * 24 && mouseY < i * 24 + 24)
		{
			DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 0, 0), false);
			DrawFormatString(8, i * 24, GetColor(125, 125, 125), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		}
	}


	// ���[�V�����̓����̃o�[
	DrawLine(500, 50, 1180, 50, GetColor(255, 255, 255));
	DrawBox(490 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680)
		, 30, 510 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680), 70, GetColor(0, 125, 125), true);


	// ���[�V�������x�̊m�F
	DrawBox(540, 20, 540 + 200, 44, GetColor(255, 255, 255), true);
	DrawBox(540, 20, 540 + 200, 44, GetColor(0, 255, 255), false);
	DrawFormatString(540, 20, GetColor(0, 0, 0), "NowSpeed : %f", nowPlayTime);


	// ���[�V�������x�̊m�F
	DrawBox(1050, 138, 1050 + 200, 162, GetColor(255, 255, 255), true);
	DrawBox(1050, 138, 1050 + 200, 162, GetColor(0, 255, 255), false);
	DrawFormatString(1050, 138, GetColor(0, 0, 0), "SoundArea : %f", soundArea[attachNum]);


	// ���[�V�������x�̕ύX
	DrawBox(1050, 170, 1050 + 200, 194, GetColor(0, 0, 0), true);
	DrawBox(1050, 170, 1050 + 200, 194, GetColor(0, 255, 255), false);
	if (CheckKeyInput(inputHandle[attachNum]) == 0)
	{
		DrawKeyInputString(1050, 170, inputHandle[attachNum]);   // ���͓r���̕������`��
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

	SoundProcess();

	for (int i = 0; i != animNum; ++i)
	{
		if (mouseX > 0 && mouseX < 200 && mouseY > i * 24 && mouseY < i * 24 + 24
			&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
		{
			Player_PlayAnim(i);
		}
	}

	if (mouseX >= 1050 && mouseX <= 1050 + 200 && mouseY > 170 && mouseY < 194
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		SetActiveKeyInput(inputHandle[attachNum]);   // ���̓n���h�����A�N�e�B�u��
	}

	if (CheckKeyInput(inputHandle[attachNum]) == 1)
	{
		soundArea[attachNum] = GetKeyInputNumberToFloat(inputHandle[attachNum]);   // ���͓r���̕������`��
	}

	if (KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		if (animSpeed[attachNum] != 0.0f)
		{
			preAnimSpeed = animSpeed[attachNum];
			animSpeed[attachNum] = 0.0f;
		}
		else
		{
			animSpeed[attachNum] = preAnimSpeed;
		}
	}

	if (mouseX >= 500 && mouseX <= 1180 && mouseY >= 20 && mouseY <= 80
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) >= 1)
	{
		nowPlayTime = ((mouseX - 500) / 680.0f) * MV1GetAttachAnimTotalTime(modelHandle, attachMotion);
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

	// �߂�ǂ��������Ǘ~�������炿����ƓK����
	if (KeyData::Get(KEY_INPUT_UP) > 0)
	{
		area.x += 10.0f;
		area.z += 10.0f;
	}

	if (KeyData::Get(KEY_INPUT_DOWN) > 0)
	{
		area.x -= 10.0f;
		area.z -= 10.0f;
	}

	if (mouseX >= 1200 && mouseX <= 1250 && mouseY >= 700 && mouseY <= 750
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		noEnd = false;
	}

	//�������̉�]�p�x���Z�b�g
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY, 0.0f));

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(area, VGet(0.0f, 120.0f, 0.0f));
}

bool Character::GetNoEnd()
{
	return noEnd;
}

void Character::SetSpeed(std::vector<float> speed)
{
	for (int i = 0; i != speed.size(); ++i)
	{
		animSpeed[i] = speed[i];
	}
}

std::vector<float> Character::GetSoundArea()
{
	return soundArea;
}

void Character::SetSound(std::vector<int> sound)
{
	for (int i = 0; i != sound.size(); ++i)
	{
		soundPlay[i] = sound[i];
	}
}

void Character::SetSoundName(std::vector<std::string> str)
{
	for (int i = 0; i != str.size(); ++i)
	{
		soundName[i] = str[i];
	}
}

std::vector<int> Character::GetSoundNumber()
{
	return soundNumber;
}

std::vector<std::string> Character::GetSoundName()
{
	return soundName;
}
