#include "InputMouse.hpp"
#include "Character.hpp"


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
	
	Character* p_character = NULL;
	p_character = new Character("model\\CLPH_motionALL.mv1");

	SetFontSize(20);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2) && KeyData::CheckEnd())
	{
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		KeyData::UpDate();

		p_character->Draw();
		p_character->Process();
	}

	delete p_character;
	p_character = NULL;

	DxLib_End();

	return 0;
}