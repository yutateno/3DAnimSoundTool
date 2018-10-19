#include <stdio.h>
#include "PlayTool.hpp"

int main(int args, char* argc)
{
	bool consoleFlag = true;
	PlayTool* playTool = NULL;
	playTool = new PlayTool();


	while (consoleFlag)
	{
		printf("起動するツールをキーボードの数字から選択してください。\n");
		printf("終了するときは適当な数値を入れてください。\n\n");

		printf("0:アニメーションツール(グラフィック用)\n");
		printf("1:サウンドツール(サウンド用)\n");

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