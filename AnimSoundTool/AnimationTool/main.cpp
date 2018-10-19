#include "InputMouse.hpp"


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

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && !MouseData::GetClick(2))
	{
		MouseData::Mouse_UpDate();
		MouseWheelData::MouseWheel_Update();
		GetMousePoint(&mouseX, &mouseY);


	}

	DxLib_End();

	return 0;
}