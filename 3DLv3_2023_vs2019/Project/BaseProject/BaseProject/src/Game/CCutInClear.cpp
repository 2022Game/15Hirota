#include "CCutInClear.h"
#include "Maths.h"

#define CUTIN_TIME 4.0f
#define START_ANGLE 0.0f
#define END_ANGLE 90.0f
#define START_Y 0.0f
#define END_Y 15.0f
#define START_DIST 5.0f
#define END_DIST 30.0f
#define WAIT_TIME 1.0f

// コンストラクタ
CCutInClear::CCutInClear()
	: mCutInStep(0)
	, mElapsedTime(0.0f)
	, mCenterPos(CVector::zero)
	, mStartAngleY(0.0f)
	, mStartAngleZ(0.0f)
{

}

// デストラクタ
CCutInClear::~CCutInClear()
{

}

// カットイン開始
bool CCutInClear::Start()
{
	// ベースのカットイン開始処理
	if (!CCutInCamera::Start()) return false;

	// カットイン時に使用する変数などの初期化
	mCutInStep = 0;
	mElapsedTime = 0.0f;

	return true;
}

// カットイン終了
bool CCutInClear::End()
{
	// ベースのカットイン終了処理
	if (!CCutInCamera::End()) return false;

	return true;
}

// カットインに必要な情報を設定
void CCutInClear::Setup(CObjectBase* obj)
{
	// 設定されたオブジェクトの位置を中心地点とする
	mCenterPos = obj->Position();
	// 設定されたオブジェクトの現在のY軸の角度を取得
	mStartAngleY = obj->EulerAngles().Y();

	mStartAngleZ = obj->EulerAngles().Z();

	mObject = obj;
}

// ステップ0 カメラの回転
void CCutInClear::CutInStep0()
{
	// カットインの時間が経過するにつれてカメラを移動させます
	if (mElapsedTime < CUTIN_TIME)
	{
		float per = mElapsedTime / CUTIN_TIME;

		// プレイヤーの位置と角度を取得
		CVector playerPos = mObject->Position();
		float playerAngleY = mObject->EulerAngles().Y();

		// カメラの位置と注視点をプレイヤーの位置と角度に合わせる
		CVector offsetPos = CVector::zero;
		offsetPos.Y(15.0f);

		float dist = Math::Lerp(50.0f, 30.0f, per);

		mAt = playerPos + offsetPos;
		mEye = mAt + CVector(0.0f, 0.0f, 1.0f) * dist; // 回転なしで直線的に移動する

		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		// 何もしない。カメラの位置を変更しない
		mCutInStep++;
		mElapsedTime = 0.0f;
	}
}

// ステップ0 カットイン終了時の待ち
void CCutInClear::CutInStep1()
{
	if (mElapsedTime < 6.0f)
	{
		mElapsedTime += Time::DeltaTime();
	}
	else
	{
		mCutInStep = 0;
		//End();
	}
}

// 更新
void CCutInClear::Update()
{
	// カットイン再生中でなければ、処理しない
	if (!mIsPlaying) return;

	switch (mCutInStep)
	{
	case 0:
		CutInStep0();
		break;
	case 1:
		CutInStep1();
		break;
	}

	// カメラの更新
	CCamera::Update();
}