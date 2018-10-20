#include "PlayTool.hpp"

void PlayTool::Process(TOOLSELECT tool)
{
	result = TRUE;		// ゲームの起動を始めた合図


	PROCESS_INFORMATION pInfo = {};	// プロセス軌道のためのもの


	STARTUPINFO sInfo = {};			// 初期プロセス起動のためのもの


	ZeroMemory(&sInfo, sizeof(sInfo));		// 構造体全部初期化する
	sInfo.cb = sizeof(sInfo);
	ZeroMemory(&pInfo, sizeof(pInfo));


	GetStartupInfo(&sInfo);					// スタートアップ情報を得る


	// ランチャーが見えない状態で起動させる
	sInfo.dwFlags = STARTF_USESHOWWINDOW;
	sInfo.wShowWindow = SW_HIDE;


	// ディレクトリ位置を調べる用変数
	std::string gamePath = "";				// ゲームexeファイル
	std::string direPath = "";				// ゲームファイル

	GetModuleFileName(NULL, Path, MAX_PATH);	// この実行ファイルの完全パスを取得

	_splitpath(Path, drive, dir, fname, ext);	// パス名を構成要素に分解する

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

	// ゲームを起動
	result = CreateProcess(
		NULL,
		(LPSTR)gamePath.c_str(),		// ゲームを指定
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_PROCESS_GROUP,
		NULL,
		direPath.c_str(),				// カレントディレクトリを指定
		&sInfo,
		&pInfo
	);


	WaitForSingleObject(pInfo.hProcess, INFINITE);		// 終了するまで待機
	CloseHandle(pInfo.hProcess);						// 解放
	CloseHandle(pInfo.hThread);							// 解放


	result = FALSE;										// ランチャーへの合図
}

bool PlayTool::GetbResult()
{
	return result;
}