#pragma once
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#pragma warning(disable : 4996)

enum class TOOLSELECT { graphic, sound };

class PlayTool
{
private:
	BOOL result;		// プロセスが起動したかどうか

	// ランチャーのパスに関する
	char Path[MAX_PATH + 1];	// 実行ファイルの完全パスを取得する変数

	char drive[MAX_PATH + 1]	// ドライブ
		, dir[MAX_PATH + 1]		// ディレクトリパス
		, fname[MAX_PATH + 1]	// ファイル名
		, ext[MAX_PATH + 1];	// ファイル名の拡張子


public:
	PlayTool() : result(FALSE) {}		// コンストラクタ
	~PlayTool() {}	// デストラクタ


	void Process(TOOLSELECT tool);		// メイン/ exeの階層までのパスを保存した引数とexeの名前を保存した引数


	// ゲッター
	bool GetbResult();		// 起動を確認
};