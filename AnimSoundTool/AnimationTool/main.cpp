#include "InputMouse.hpp"
#include "Character.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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

	int mouseX, mouseY;

	Character* p_character = NULL;
	p_character = new Character();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2))
	{
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		GetMousePoint(&mouseX, &mouseY);

		p_character->Draw();
		p_character->Process();
	}

	delete p_character;
	p_character = NULL;

	DxLib_End();

	return 0;
}