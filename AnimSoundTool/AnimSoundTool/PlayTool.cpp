#include "PlayTool.hpp"

void PlayTool::Process(TOOLSELECT tool)
{
	result = TRUE;		// �Q�[���̋N�����n�߂����}


	PROCESS_INFORMATION pInfo = {};	// �v���Z�X�O���̂��߂̂���


	STARTUPINFO sInfo = {};			// �����v���Z�X�N���̂��߂̂���


	ZeroMemory(&sInfo, sizeof(sInfo));		// �\���̑S������������
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));


	GetStartupInfo(&sInfo);					// �X�^�[�g�A�b�v���𓾂�


	// �����`���[�������Ȃ���ԂŋN��������
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;


	// �f�B���N�g���ʒu�𒲂ׂ�p�ϐ�
	std::string gamePath = "";				// �Q�[��exe�t�@�C��
	std::string direPath = "";				// �Q�[���t�@�C��

	GetModuleFileName(NULL, Path, MAX_PATH);	// ���̎��s�t�@�C���̊��S�p�X���擾

	_splitpath(Path, drive, dir, fname, ext);	// �p�X�����\���v�f�ɕ�������

	gamePath.operator+= (drive);
	gamePath.operator+= (dir);
	gamePath.operator+= ("\\");
	gamePath.operator+= ("game");
	gamePath.operator+= ("\\");

	direPath = gamePath;

	switch (tool)
	{
	case TOOLSELECT::graphic:
		gamePath.operator+= ("AnimationTool");
		gamePath.operator+= (".exe");
		break;

	case TOOLSELECT::sound:
		gamePath.operator+= ("SoundTool");
		gamePath.operator+= (".exe");
		break;
	}

	// �Q�[�����N��
	result = CreateProcess(
		NULL,
		(LPSTR)gamePath.c_str(),		// �Q�[�����w��
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_PROCESS_GROUP,
		NULL,
		direPath.c_str(),				// �J�����g�f�B���N�g�����w��
		&sInfo,
		&pInfo
	);


	WaitForSingleObject(pInfo.hProcess, INFINITE);		// �I������܂őҋ@
	CloseHandle(pInfo.hProcess);						// ���
	CloseHandle(pInfo.hThread);							// ���


	result = FALSE;										// �����`���[�ւ̍��}
}

bool PlayTool::GetbResult()
{
	return result;
}