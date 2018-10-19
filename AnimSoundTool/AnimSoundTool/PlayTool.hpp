#pragma once
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#pragma warning(disable : 4996)

enum class TOOLSELECT { graphic, sound };

class PlayTool
{
private:
	BOOL result;		// �v���Z�X���N���������ǂ���

	// �����`���[�̃p�X�Ɋւ���
	char Path[MAX_PATH + 1];	// ���s�t�@�C���̊��S�p�X���擾����ϐ�

	char drive[MAX_PATH + 1]	// �h���C�u
		, dir[MAX_PATH + 1]		// �f�B���N�g���p�X
		, fname[MAX_PATH + 1]	// �t�@�C����
		, ext[MAX_PATH + 1];	// �t�@�C�����̊g���q


public:
	PlayTool() : result(FALSE) {}		// �R���X�g���N�^
	~PlayTool() {}	// �f�X�g���N�^


	void Process(TOOLSELECT tool);		// ���C��/ exe�̊K�w�܂ł̃p�X��ۑ�����������exe�̖��O��ۑ���������


	// �Q�b�^�[
	bool GetbResult();		// �N�����m�F
};