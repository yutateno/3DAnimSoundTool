#include "InputMouse.hpp"
#include "Character.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define _POINTER_RELEASE(p) {if(p!=NULL){delete p; p=NULL;}}

std::vector<std::string> SearchDrawFile();
inline void AutoSaveData(std::string str, std::vector<float> speed);
inline void SaveData(std::string str, std::vector<float> speed);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);   // ���O�o�͂��s��Ȃ�

	SetWindowText("AnimationTool");

	SetBackgroundColor(100, 100, 100);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	ChangeWindowMode(TRUE);

	SetUseLarge3DPositionSupport(TRUE);

	SetGraphMode(1280, 768, 32);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetAlwaysRunFlag(TRUE);

	SetDragFileValidFlag(TRUE);

	SetMouseDispFlag(TRUE);

	SetDrawScreen(DX_SCREEN_BACK);

	Character* p_mainCharacter = NULL;

	std::vector<std::string> str = SearchDrawFile();


	SetFontSize(20);

	bool charaCreate = false;

	int mouseX, mouseY;

	std::string nowFile = "";

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2) && KeyData::CheckEnd())
	{
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		KeyData::UpDate();


		if (charaCreate)
		{
			GetMousePoint(&mouseX, &mouseY);

			p_mainCharacter->Draw();
			p_mainCharacter->Process();

			// ���f���M��I��
			DrawBox(12, 700, 62, 750, GetColor(0, 255, 255), true);
			DrawBox(12, 700, 62, 750, GetColor(125, 125, 125), false);
			DrawFormatString(17, 715, GetColor(0, 0, 0), "Save");

			if (mouseX >= 12 && mouseX <= 12 + 50 && mouseY > 700 && mouseY < 750
				&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)))
			{
				SaveData(nowFile, p_mainCharacter->GetSpeed());
			}

			if (!p_mainCharacter->GetNoEnd())
			{
				AutoSaveData(nowFile, p_mainCharacter->GetSpeed());
				charaCreate = false;
				_POINTER_RELEASE(p_mainCharacter);
			}
		}
		else
		{
			GetMousePoint(&mouseX, &mouseY);

			for (int i = 0; i != str.size(); ++i)
			{
				DrawBox(100, 400 + 20 * i, 100 + 500, 420 + 20 * i, GetColor(0, 255, 255), true);
				DrawBox(100, 400 + 20 * i, 100 + 500, 420 + 20 * i, GetColor(0, 0, 0), false);
				DrawFormatString(100, 400 + 20 * i, GetColor(0, 0, 0), "%s", str[i].c_str());

				if (mouseX >= 100 && mouseX <= 100 + 500 && mouseY > 400 + 20 * i && mouseY < 420 + 20 * i
					&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)))
				{
					charaCreate = true;
					p_mainCharacter = new Character(str[i].c_str());
					nowFile = str[i].c_str();
				}
			}
		}
	}

	if (p_mainCharacter != NULL)
	{
		AutoSaveData(nowFile, p_mainCharacter->GetSpeed());
	}

	_POINTER_RELEASE(p_mainCharacter);

	DxLib_End();

	return 0;
}

std::vector<std::string> SearchDrawFile()
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	std::string file = "media\\model\\*.mv1";

	std::vector<std::string> mediaFile;	// �Ԃ�l
	std::vector<std::string> reFile;	// �Ԃ�l

	HANDLE hFind;
	WIN32_FIND_DATA FindFileData;

	hFind = FindFirstFile(file.c_str(), &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			mediaFile.push_back(FindFileData.cFileName);

		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	reFile.resize(mediaFile.size());
	for (int i = 0; i != reFile.size(); ++i)
	{
		reFile[i] = "media\\model\\";
		reFile[i].append(mediaFile[i]);
	}

	return reFile;
}


inline void SaveData(std::string str, std::vector<float> speed)
{
	std::ofstream saveFile;
	std::string file = str;
	file.erase(file.end() - 3, file.end());
	file.append("csv");
	saveFile.open(file.c_str());		// �t�@�C���I�[�v��

	if (saveFile.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}
	else {
		// �ǂݍ��ݐ���
		for (int i = 0; i != speed.size(); ++i)
		{
			saveFile << i << "," << speed[i];
			saveFile << std::endl;
		}
	}

	// �t�@�C�������
	saveFile.close();
}

inline void AutoSaveData(std::string str, std::vector<float> speed)
{
	std::ofstream saveFile;
	std::string file = str;
	file.erase(file.end() - 4, file.end());
	file.append("_AutoSave.csv");
	saveFile.open(file.c_str());		// �t�@�C���I�[�v��

	if (saveFile.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}
	else {
		// �ǂݍ��ݐ���
		for (int i = 0; i != speed.size(); ++i)
		{
			saveFile << i << "," << speed[i];
			saveFile << std::endl;
		}
	}

	// �t�@�C�������
	saveFile.close();
}