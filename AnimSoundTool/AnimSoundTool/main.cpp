#include <stdio.h>
#include "PlayTool.hpp"

int main(int args, char* argc)
{
	bool consoleFlag = true;
	PlayTool* playTool = NULL;
	playTool = new PlayTool();


	while (consoleFlag)
	{
		printf("�N������c�[�����L�[�{�[�h�̐�������I�����Ă��������B\n");
		printf("�I������Ƃ��͓K���Ȑ��l�����Ă��������B\n\n");

		printf("0:�A�j���[�V�����c�[��(�O���t�B�b�N�p)\n");
		printf("1:�T�E���h�c�[��(�T�E���h�p)\n");

		int toolFlag = 5;
		scanf_s("%d", &toolFlag);

		switch (toolFlag)
		{
		case 0:
			playTool->Process(static_cast<TOOLSELECT>(toolFlag));
			break;

		case 1:
			playTool->Process(static_cast<TOOLSELECT>(toolFlag));
			break;

		default:
			consoleFlag = false;
			break;
		}
	}

	if (playTool != NULL)
	{
		delete playTool;
		playTool = NULL;
	}

	return 0;
}