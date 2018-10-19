#include "Character.hpp"



Character::Character()
{
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("model\\CLPH_motionALL.mv1");

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(1.0f, 1000.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 170, -200), VGet(0.0f, 120.0f, 0.0f));

	// ３Ｄモデルの1番目のアニメーションをアタッチする
	attachIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);

	// 再生時間の初期化
	playTime = 0.0f;

	angleY = 0.0f;
}


Character::~Character()
{
	MV1DeleteModel(modelHandle);
}

void Character::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}

void Character::Process()
{
	// 再生時間を進める
	playTime += 0.2f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (playTime >= totalTime)
	{
		playTime = 0.0f;
	}

	// 再生時間をセットする
	MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

	if (CheckHitKey(KEY_INPUT_LEFT) > 0)
	{
		angleY -= ROTATE_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) > 0) 
	{
		angleY += ROTATE_SPEED;
	}

	//第二引数の回転角度をセット
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY, 0.0f));
}
