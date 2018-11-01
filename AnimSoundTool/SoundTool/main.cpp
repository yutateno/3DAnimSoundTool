#include "InputMouse.hpp"
#include "Character.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#define _POINTER_RELEASE(p) {if(p!=NULL){delete p; p=NULL;}}

std::vector<std::string> SearchDrawFile();
std::vector<std::string> SearchCSVFile();
std::vector<float> FileOpenSpeed(std::string str);
std::vector<std::string> SearchSoundName();
std::vector<int> SearchSoundFile();

inline void AutoSaveData(std::string str, std::vector<float> speed, std::vector<std::string> soundFile, std::vector<int> soundNumber);
inline void SaveData(std::string str, std::vector<float> speed, std::vector<std::string> soundFile, std::vector<int> soundNumber);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);   // ���O�o�͂��s��Ȃ�

	SetWindowText("SoundTool");

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

	std::vector<std::string> csvFile = SearchCSVFile();

	std::vector<int> sound = SearchSoundFile();

	std::vector<std::string> soundName = SearchSoundName();

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
				SaveData(nowFile, p_mainCharacter->GetSoundArea(), p_mainCharacter->GetSoundName(), p_mainCharacter->GetSoundNumber());
			}

			if (!p_mainCharacter->GetNoEnd())
			{
				AutoSaveData(nowFile, p_mainCharacter->GetSoundArea(), p_mainCharacter->GetSoundName(), p_mainCharacter->GetSoundNumber());
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
				DrawFormatString(100, 400 + 20 * i, GetColor(0, 0, 0), "%s", csvFile[i].c_str());

				if (mouseX >= 100 && mouseX <= 100 + 500 && mouseY > 400 + 20 * i && mouseY < 420 + 20 * i
					&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)))
				{
					charaCreate = true;
					p_mainCharacter = new Character(str[i].c_str(), static_cast<int>(sound.size()));
					nowFile = str[i].c_str();
					p_mainCharacter->SetSpeed(FileOpenSpeed(nowFile));
					p_mainCharacter->SetSound(sound);
					p_mainCharacter->SetSoundName(soundName);
				}
			}
		}
	}

	if (p_mainCharacter != NULL)
	{
		AutoSaveData(nowFile, p_mainCharacter->GetSoundArea(), p_mainCharacter->GetSoundName(), p_mainCharacter->GetSoundNumber());
	}

	_POINTER_RELEASE(p_mainCharacter);

	DxLib_End();

	return 0;
}

std::vector<std::string> SearchDrawFile()
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	std::string file = "media\\model\\*.csv";

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
		reFile[i].erase(reFile[i].end() - 3, reFile[i].end());
		reFile[i].append("mv1");
	}

	return reFile;
}

std::vector<std::string> SearchCSVFile()
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	std::string file = "media\\model\\*.csv";

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
		reFile[i].erase(reFile[i].end() - 3, reFile[i].end());
		reFile[i].append("csv");
	}

	return reFile;
}

std::vector<float> FileOpenSpeed(std::string str)
{
	std::string openFile = str;
	openFile.erase(openFile.end() - 3, openFile.end());
	openFile.append("csv");
	std::ifstream ifs(openFile.c_str());

	if (!ifs)
	{
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}

	std::vector<float> reFloat;
	std::string strFile = "";

	// �t�@�C���̒��g����s���ǂݎ��
	while (getline(ifs, strFile))
	{
		reFloat.push_back(stof(strFile));
	}

	return reFloat;
}

std::vector<std::string> SearchSoundName()
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	std::string file = "media\\sound\\*.wav";

	std::vector<std::string> mediaFile;	// �Ԃ�l

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

	return mediaFile;
}

std::vector<int> SearchSoundFile()
{
	// �g���q�����t�@�C���̖��O�𒲂ׂ�
	std::string file = "media\\sound\\*.wav";

	std::vector<std::string> mediaFile;	// �Ԃ�l
	std::string temp;
	std::vector<int> reFile;	// �Ԃ�l

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
		temp = "media\\sound\\";
		temp.append(mediaFile[i]);
		reFile[i] = LoadSoundMem(temp.c_str());
	}

	return reFile;
}


inline void SaveData(std::string str, std::vector<float> speed, std::vector<std::string> soundFile, std::vector<int> soundNumber)
{
	std::ofstream saveFile;
	std::string file = str;
	file.erase(file.end() - 3, file.end());
	file.append("cyn");
	saveFile.open(file.c_str());		// �t�@�C���I�[�v��

	if (saveFile.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}
	else {
		// �ǂݍ��ݐ���
		for (int i = 0; i != speed.size(); ++i)
		{
			if (soundNumber[i] != -1)
			{
				saveFile << i << "," << speed[i] << "," << soundFile[soundNumber[i]];
				saveFile << std::endl;
			}
			else
			{
				saveFile << i << "," << speed[i] << "," << soundFile[0];
				saveFile << std::endl;
			}
		}
	}

	// �t�@�C�������
	saveFile.close();
}

inline void AutoSaveData(std::string str, std::vector<float> speed, std::vector<std::string> soundFile, std::vector<int> soundNumber)
{
	std::ofstream saveFile;
	std::string file = str;
	file.erase(file.end() - 4, file.end());
	file.append("_AutoSave.cyn");
	saveFile.open(file.c_str());		// �t�@�C���I�[�v��

	if (saveFile.fail()) {	// �t�@�C���ǂݍ��ݎ��s
		DrawFormatString(0, 0, GetColor(0, 0, 0), "SaveError");
	}
	else {
		// �ǂݍ��ݐ���
		for (int i = 0; i != speed.size(); ++i)
		{
			if (soundNumber[i] != -1)
			{
				saveFile << i << "," << speed[i] << "," << soundFile[soundNumber[i]];
				saveFile << std::endl;
			}
			else
			{
				saveFile << i << "," << speed[i] << "," << soundFile[0];
				saveFile << std::endl;
			}
		}
	}

	// �t�@�C�������
	saveFile.close();
}