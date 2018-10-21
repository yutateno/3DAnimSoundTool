#include "InputMouse.hpp"
#include "Character.hpp"

#define _POINTER_RELEASE(p) {if(p!=NULL){delete p; p=NULL;}}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);   // ƒƒOo—Í‚ðs‚í‚È‚¢

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

	std::string str[2];
	str[0] = "media\\model\\CLPH_motionALL.mv1";
	str[1] = "media\\model\\sd_,motionALL.mv1";

	SetFontSize(20);

	bool charaCreate = false;

	int mouseX, mouseY;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2) && KeyData::CheckEnd())
	{
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		KeyData::UpDate();

		if (charaCreate)
		{
			p_mainCharacter->Draw();
			p_mainCharacter->Process();
			if (!p_mainCharacter->GetNoEnd())
			{
				charaCreate = false;
				_POINTER_RELEASE(p_mainCharacter);
			}
		}
		else
		{
			GetMousePoint(&mouseX, &mouseY);

			DrawBox(100, 400, 100 + 500, 420, GetColor(0, 255, 255), true);
			DrawBox(100, 400, 100 + 500, 420, GetColor(0, 0, 0), false);
			DrawFormatString(100, 400, GetColor(0, 0, 0), "%s", str[0].c_str());

			DrawBox(100, 420, 100 + 500, 440, GetColor(0, 255, 255), true);
			DrawBox(100, 420, 100 + 500, 440, GetColor(0, 0, 0), false);
			DrawFormatString(100, 420, GetColor(0, 0, 0), "%s", str[1].c_str());

			if (mouseX >= 100 && mouseX <= 100 + 500 && mouseY > 400 && mouseY < 420
				&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)))
			{
				charaCreate = true;
				p_mainCharacter = new Character(str[0].c_str());
			}

			if (mouseX >= 100 && mouseX <= 100 + 500 && mouseY > 420 && mouseY < 440
				&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)))
			{
				charaCreate = true;
				p_mainCharacter = new Character(str[1].c_str());
			}
		}
	}

	_POINTER_RELEASE(p_mainCharacter);

	DxLib_End();

	return 0;
}