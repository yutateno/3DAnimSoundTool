#include "Character.hpp"

// 使うアニメーション管理
void Character::Player_PlayAnim(int attach)
{
	// 今のモーションが違うものだったら
	if (attachNum != attach)
	{
		// 直前のモーションが有効だったらデタッチする
		if (preAttach != -1 && motionBlendTime < 1.0f)
		{
			MV1DetachAnim(modelHandle, preAttach);
			preAttach = -1;
		}
		// 今のモーションを入れる
		preAttach = attachMotion;
		preMotionPlayTime = nowPlayTime;

		// 引数を今のモーション番号に入れる
		attachNum = attach;

		// 新たに指定のモーションをモデルにアタッチする
		attachMotion = MV1AttachAnim(modelHandle, attachNum, -1, false);

		// 動作時間を初期化する
		nowPlayTime = 0.0f;

		// ブレンド率は直前のモーションが有効ではない場合は１．０ｆ( 再生中のモーション１が１００％の状態 )にする
		if (preMotionPlayTime == -1)
		{
			motionBlendTime = 1.0f;
		}
		else
		{
			motionBlendTime = 0.0f;
		}
	}
}

// 全てのアニメーションの管理
void Character::Player_AnimProcess()
{
	// ブレンド率が１以下の場合は１に近づける
	if (motionBlendTime < 1.0)
	{
		motionBlendTime += 0.075f;
		if (motionBlendTime >= 1.0f)
		{
			motionBlendTime = 1.0f;
		}
	}

	// 再生している現在のモーションの処理
	if (attachMotion != -1)
	{
		// モーションの総時間を取得
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachMotion);

		// 再生時間を進める
		nowPlayTime += animSpeed;


		// 再生時間が総時間に到達していたらループさせる
		if (nowPlayTime >= totalTime)
		{
			nowPlayTime = fmodf(nowPlayTime, totalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, attachMotion, nowPlayTime);

		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, attachMotion, motionBlendTime);
	}

	// 再生している直前のモーションの処理
	if (preAttach != -1)
	{
		// アニメーションの総時間を取得
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, preAttach);

		// 再生時間を進める
		preMotionPlayTime += animSpeed;

		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (preMotionPlayTime > totalTime)
		{
			preMotionPlayTime = fmodf(preMotionPlayTime, totalTime);
		}

		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(modelHandle, preAttach, preMotionPlayTime);

		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(modelHandle, preAttach, (1.0f - motionBlendTime));
	}
}


Character::Character(std::string fileName)
{
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel(fileName.c_str());

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(1.0f, 1000.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 170, -200), VGet(0.0f, 120.0f, 0.0f));

	attachNum = 1;

	// ３Ｄモデルの0番目のアニメーションをアタッチする
	attachMotion = MV1AttachAnim(modelHandle, attachNum, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachMotion);


	angleY = 0.0f;

	animSpeed = 0.3f;
	preAnimSpeed = animSpeed;
	nowPlayTime = 0.0f;
	motionBlendTime = 0.0f;
	preAttach = -1;
	preMotionPlayTime = 0.0f;

	animNum = MV1GetAnimNum(modelHandle);

	GetMousePoint(&mouseX, &mouseY);

	inputHandle = MakeKeyInput(10, FALSE, TRUE, TRUE);      // 半角英数字入力ハンドル

	noEnd = true;
}


Character::~Character()
{
	MV1DeleteModel(modelHandle);
}

void Character::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);


	// モーション番号と名前
	for (int i = 0; i != animNum; ++i)
	{
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 255, 255), true);
		DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(0, 255, 255), false);
		DrawFormatString(8, i * 24, GetColor(0, 0, 0), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		if (mouseX >= 0 && mouseX <= 200 && mouseY > i * 24 && mouseY < i * 24 + 24)
		{
			DrawBox(0, i * 24, 200, i * 24 + 24, GetColor(255, 0, 0), false);
			DrawFormatString(8, i * 24, GetColor(125, 125, 125), "%d : %s", i, MV1GetAnimName(modelHandle, i));
		}
	}

	
	// モーションの動きのバー
	DrawLine(300, 50, 980, 50, GetColor(255, 255, 255));
	DrawBox(290 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680)
		, 30, 310 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680), 70, GetColor(0, 125, 125), true);


	// モーション速度の確認
	DrawBox(1050, 38, 1050 + 200, 62, GetColor(255, 255, 255), true);
	DrawBox(1050, 38, 1050 + 200, 62, GetColor(0, 255, 255), false);
	if (animSpeed != 0.0f)
	{
		DrawFormatString(1050, 38, GetColor(0, 0, 0), "Speed : %f", animSpeed);
	}
	else
	{
		DrawFormatString(1050, 38, GetColor(0, 0, 0), "Speed : %f", preAnimSpeed);
	}


	// モーション速度の変更
	DrawBox(1050, 70, 1050 + 200, 94, GetColor(0, 0, 0), true);
	DrawBox(1050, 70, 1050 + 200, 94, GetColor(0, 255, 255), false);
	if (CheckKeyInput(inputHandle) == 0)
	{
		DrawKeyInputString(1050, 70, inputHandle);   // 入力途中の文字列を描画
	}

	
	// モーションストップ項目
	DrawFormatString(20, 600, GetColor(255, 255, 255), "スペースキーでモーションストップ");


	// モデル弄り終了
	DrawBox(1200, 700, 1250, 750, GetColor(255, 0, 0), true);
	DrawBox(1200, 700, 1250, 750, GetColor(125, 125, 125), false);
	DrawCircle(1225, 725, 10, GetColor(0, 0, 0), false);
	DrawLine(1225, 710, 1225, 720, GetColor(0, 0, 0));
}

void Character::Process()
{
	GetMousePoint(&mouseX, &mouseY);

	for (int i = 0; i != animNum; ++i)
	{
		if (mouseX >= 0 && mouseX <= 200 && mouseY > i * 24 && mouseY < i * 24 + 24
			&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
		{
			Player_PlayAnim(i);
		}
	}

	if (mouseX >= 1050 && mouseX <= 1050 + 200 && mouseY > 70 && mouseY < 94
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		SetActiveKeyInput(inputHandle);   // 入力ハンドルをアクティブに
	}

	if (CheckKeyInput(inputHandle) == 1)
	{
		animSpeed = GetKeyInputNumberToFloat(inputHandle);   // 入力途中の文字列を描画
	}

	if (KeyData::Get(KEY_INPUT_SPACE) == 1)
	{
		if (animSpeed != 0.0f)
		{
			preAnimSpeed = animSpeed;
			animSpeed = 0.0f;
		}
		else
		{
			animSpeed = preAnimSpeed;
		}
	}

	DrawLine(300, 50, 980, 50, GetColor(255, 255, 255));
	DrawBox(290 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680)
		, 30, 310 + static_cast<int>((nowPlayTime / MV1GetAttachAnimTotalTime(modelHandle, attachMotion)) * 680), 70, GetColor(0, 125, 125), true);

	if (mouseX >= 300 && mouseX <= 980 && mouseY >= 20 && mouseY <= 80
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) >= 1)
	{
		nowPlayTime = ((mouseX - 300) / 680.0f) * MV1GetAttachAnimTotalTime(modelHandle, attachMotion);
	}

	Player_AnimProcess();

	if (KeyData::Get(KEY_INPUT_LEFT) > 0)
	{
		angleY -= ROTATE_SPEED;
	}

	if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
	{
		angleY += ROTATE_SPEED;
	}

	if (mouseX >= 1200 && mouseX <= 1250 && mouseY >= 700 && mouseY <= 750
		&& MouseData::GetClick(static_cast<int>(CLICK::LEFT)) == 1)
	{
		noEnd = false;
	}

	//第二引数の回転角度をセット
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY, 0.0f));
}

bool Character::GetNoEnd()
{
	return noEnd;
}
