#include "CXPlayer.h"

#define VELOCITY CVector(0.0f, 0.0f, 0.1f) //移動速度
#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //回転速度


CXPlayer::CXPlayer()
	:mColSpherBody(this, nullptr, CVector(), 0.5f)
	, mColSpherHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	,mColspherSword(this,nullptr,CVector(-10.0f,10.0f,50.0f),0.3f, CCollider::ETag::ESWORD)
{
	mTag = EPLAYER;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列
	//体
	mColSpherBody.Matrix(&mpCombinedMatrix[9]);
	//頭
	mColSpherHead.Matrix(&mpCombinedMatrix[12]);
	//剣
	mColspherSword.Matrix(&mpCombinedMatrix[22]);
}

void CXPlayer::Update()
{
	if (mInput.Key(VK_SPACE))
	{
		if (AnimationIndex() != 3 && AnimationIndex() != 4)
		{
			ChangeAnimation(3, false, 30);  //アニメーション3
		}
	}
	if (AnimationIndex() == 3 || AnimationIndex() == 4)
	{
		if (IsAnimationFinished())
		{
			if (AnimationIndex() == 3)
			{
				ChangeAnimation(4, false, 30);  // アニメーション4
			}
			else if (AnimationIndex() == 4)
			{
				ChangeAnimation(0, true, 60);  // アニメーション0
			}
		}
		CXCharacter::Update();
		return;
	}

	//カメラの前方
	CVector cameraZ = CActionCamera::Instance()->VectorZ();
	//カメラの左方向
	CVector cameraX = CActionCamera::Instance()->VectorX();
	//キャラクタの前方
	CVector charZ = mMatrixRotate.VectorZ();
	//XZ平面にして正規化
	cameraZ.Y(0.0f); cameraZ = cameraZ.Normalize();
	cameraX.Y(0.0f); cameraX = cameraX.Normalize();
	charZ.Y(0.0f); charZ = charZ.Normalize();
	//移動方向の設定
	CVector move;
	bool AnimeChangeflag = false;

	if (mInput.Key('A')) {
		move = move + cameraX;
		AnimeChangeflag = true;
	}
	if (mInput.Key('D')) {
		move = move - cameraX;
		AnimeChangeflag = true;
	}
	if (mInput.Key('W')) {
		move = move + cameraZ;
		AnimeChangeflag = true;
	}
	if (mInput.Key('S')) {
		move = move - cameraZ;
		AnimeChangeflag = true;
	}
	if (AnimeChangeflag)
	{
		ChangeAnimation(1, true, 60);
	}
	else
	{
		ChangeAnimation(0, true, 60);
	}
	//移動有り
	if (move.Length() > 0.0f)
	{
		//遊び
		const float MARGIN = 0.06f;
		//正規化
		move = move.Normalize();
		//自分の向きと向かせたい向きで外積
		float cross = charZ.Cross(move).Y();
		//自分の向きと向かせたい向きで内積
		float dot = charZ.Dot(move);
		//外積がプラスは左回転
		if (cross > MARGIN) {
			mRotation.Y(mRotation.Y() + 5.0f);
		}
		//外積がマイナスは右回転
		else if (cross < -MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//前後の向きが同じとき内積は1.0
		else if (dot < 1.0f - MARGIN) {
			mRotation.Y(mRotation.Y() - 5.0f);
		}
		//移動方向へ移動
		mPosition = mPosition + move * 0.1f;
		ChangeAnimation(1, true, 60);
	}

	CXCharacter::Update();
}

//if (mInput.Key('A'))
	//{
	//	mRotation = mRotation + ROTATION_YV;
	//}
	//if (mInput.Key('D'))
	//{
	//	mRotation = mRotation - ROTATION_YV;
	//}
	//if (mInput.Key('S')) 
	//{
	//	mRotation = mRotation - ROTATION_YV;
	//}
	//if (mInput.Key('W'))
	//{
	//	mPosition = mPosition + VELOCITY * mMatrixRotate;
	//	ChangeAnimation(1, true, 60);
	//}
	//else
	//{
	//	if (AnimationIndex() != 3 && AnimationIndex() != 4)
	//	{
	//		ChangeAnimation(0, true, 60);	//アニメーション0
	//	}
	//}