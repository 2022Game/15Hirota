//プレイヤークラスのインクルード
#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.05f,0.0f)	//重力加速度

#define JUMP_START CVector(0.0f,0.75f,0.0f)	//ジャンプ初速

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //移動速度
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //回転速度

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sHp = 0;	//Hp

CPlayer::CPlayer()
	: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 5.0f), CVector(0.0f, 3.5f, -5.0f))		//前後
	, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, -0.5f, 0.0f))		//上下
	, mLine3(this, &mMatrix, CVector(3.5f, 3.5f, 0.0f), CVector(-3.5f, 3.5f, 0.0f))	//左右
	,mJumpcount(0)
{
	//インスタンスの設定
	spInstance = this;
	sHp = HP;
}

//CPlayer(位置, 回転, スケール)
CPlayer::CPlayer(const CVector& pos, const CVector& rot, const CVector& scale)
{
	CTransform::Update(pos, rot, scale); //行列の更新
}

int CPlayer::Hp()	//HP
{
	return sHp;
}

//更新処理
void CPlayer::Update() {
	
	//Dキー入力で回転
	if (mInput.Key('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATION_YV;
	}
	//Aキー入力で回転
	if (mInput.Key('A')) {
		//Y軸の回転値を減少
		mRotation = mRotation + ROTATION_YV;
	}
	//Sキー入力で後退
	if (mInput.Key('S')) {
		//後ろに下がる
		Position(Position() - VELOCITY * MatrixRotate());
	}
	//Wキー入力で前進
	if (mInput.Key('W')) {
		//前方向に進む
		Position(Position() + VELOCITY * MatrixRotate());
	}
	if (mInput.Key(VK_SHIFT))	//ダッシュ処理
	{
		if (mInput.Key('W') || mInput.Key('A') || mInput.Key('D'))
		{
			Position(Position() + CVector(0.0f, 0.0f, 0.20f) * mMatrixRotate);
		}
		else
		{
			//何もしないであってる？
		}
	}
	bool isGrounded = mPosition.Y() <= 0.0f || mVelocity.Y() == 0.0f;	//接地しているか
	bool isJumpKeyPressed = mInput.PushKey(VK_SPACE);	//押しているか

	if (isJumpKeyPressed) {
		if ((mJumpcount == 0 && isGrounded) || (mVelocity.Y() <= 0.0f && isGrounded)) {
			// ジャンプ処理
			mVelocity = JUMP_START * MatrixRotate();
			mJumpcount = 1;
		}
	}
	if (GetKeyState(VK_LBUTTON) & 0x80) {	//マウス左　攻撃
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * Matrix());
		bullet->Rotation(mRotation);
		bullet->Update();
		/*CApplication::TaskManager()->Add(bullet);
		bullet.Set(0.1f, 1.5f);
		bullet.Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet.Rotation(mRotation);*/
	}
	if (GetKeyState(VK_RBUTTON) & 0x80) {
		//未定
	}
	if (GetKeyState(VK_MBUTTON) & 0x80) {
		//未定
	}

	//変換行列の更新
	CTransform::Update();
	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());

	// 重力処理
	if (!isGrounded) {
		mVelocity = mVelocity + GRAVITY;
		Position(Position() + GRAVITY);
	}

	//移動処理
	Position(Position() + mVelocity);

	////上昇中または着地した場合の処理
	//	if (mJumpcount > 0 && mVelocity.Y() > 0.0f) {
	//		mJumpcount = 0; //空中でのジャンプを無効化
	//	}

	// 上昇中または着地した場合の処理
	if (mJumpcount > 0 && mVelocity.Y() > 0.0f && !isJumpKeyPressed) {
		mJumpcount = 0; // 空中でのジャンプを無効化
	}

	if (isGrounded && mVelocity.Y() <= 0.0f) {
		Position(CVector(mPosition.X(), 0.0f, mPosition.Z()));
		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
		if (isGrounded) {
			mJumpcount = 0; //地面に着地したらジャンプカウントをリセット
		}
	}

	//復活処理に使えるかも？
	//位置が画面外に出た場合は初期位置に戻す
	/*if (mPosition.Y() < -10.0f)
	{
		mPosition = CVector(0.0f, 0.0f, 0.0f);
		mVelocity = CVector(0.0f, 0.0f, 0.0f);
	}*/
}

//プレイヤーのインスタンス
CPlayer* CPlayer::Instance()
{
	return spInstance;
}

void CPlayer::Collision()
{
	//コライダの優先度変更
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//mLine4.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Instance()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Instance()->Collision(&mLine3, COLLISIONRANGE);
}

void CPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE://線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {2;
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			if (CCollider::CollisionTriangleLine(o, m, &adjust)){
				//位置の更新(mPosition + adjust)
				Position(Position() + adjust);

				//行列の更新
				CTransform::Update();
			}
		}
		break;
	}
}