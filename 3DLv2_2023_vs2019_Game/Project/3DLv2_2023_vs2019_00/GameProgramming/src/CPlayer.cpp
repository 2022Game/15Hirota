//プレイヤークラスのインクルード
#include "CPlayer.h"
#include "CApplication.h"
#include "CCollisionManager.h"
#include "CRectangle.h"

#define HP 100	//hp

#define GRAVITY CVector(0.0f,-0.05f,0.0f)	//重力加速度

#define JUMP_HGIT CVector(0.0f,5.0f,0.0f)	//ジャンプの高さ
#define JUMP_SHOKI CVector(0.0f,1.0f,0.0f)	//ジャンプの初速
#define JUMP_OWARI CVector(0.0f,-0.5f,0.0f)	//ジャンプの終わりの速度
#define AIR_RESISTANCE CVector(0.0f,-0.5f,0.0f)	//空気抵抗

#define ROTATION_YV	CVector(0.0f, 2.0f, 0.0f) //回転速度
#define VELOCITY CVector(0.0f, 0.0f, 0.3f) //移動速度
#define ROTATION_XV	CVector(2.0f, 0.0f, 0.0f) //回転速度

CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::sHp = 0;	//Hp


CPlayer::CPlayer()
	: mLine(this, &mMatrix, CVector(0.0f, 3.5f, 4.5f), CVector(0.0f, 3.5f, -4.5f))		//前後
	, mLine2(this, &mMatrix, CVector(0.0f, 6.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f))		//上下
	, mLine3(this, &mMatrix, CVector(2.5f, 3.5f, 0.0f), CVector(-2.5f, 3.5f, 0.0f))	//左右
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

int CPlayer::Hp()
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
		mPosition = mPosition - VELOCITY * mMatrixRotate;
	}
	//Wキー入力で前進
	if (mInput.Key('W')) {
		//前方向に進む
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	if (mInput.Key(VK_SHIFT))
	{
		if (mInput.Key('W') || mInput.Key('A') || mInput.Key('D'))
		{
			mPosition = mPosition + CVector(0.0f, 0.0f, 0.20f) * mMatrixRotate;
		}
		else
		{
			//何もしないであってるか？
		}
	}
	//スペースキー入力でジャンプ
	if (mInput.PushKey(VK_SPACE)) {

		if (mJumpcount == 0 && mPosition.Y() <= 0.0f)
		{
			//// ジャンプ処理
			mPosition = mPosition + JUMP_SHOKI + JUMP_HGIT * mMatrixRotate;
			mJumpcount++;
		}
		else if (mJumpcount > 0 && mInput.PushKey(VK_SPACE) && mPosition.Y() > 4.0f) {
			//ジャンプ中の処理
			mVelocity = mVelocity + GRAVITY + AIR_RESISTANCE;
			mJumpcount++;
			/*mPosition = mPosition + JUMP_HGIT + JUMP_OWARI * mMatrixRotate;
			mVelocity = mVelocity - AIR_RESISTANCE;*/
			mJumpcount++;
		}
		if (mInput.Key(VK_SPACE) && mPosition.Y() < 2.0f)
		{
			mVelocity = mVelocity - AIR_RESISTANCE * mMatrixRotate;
		}
	}
	else if (!mInput.Key(VK_SPACE) && !(mPosition.Y() <= 0.0f))
	{
		mJumpcount = 0;
	}
	if (GetKeyState(VK_LBUTTON) & 0x80) {
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
		/*CApplication::TaskManager()->Add(bullet);
		bullet.Set(0.1f, 1.5f);
		bullet.Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet.Rotation(mRotation);*/
	}
	if (GetKeyState(VK_RBUTTON) & 0x80) {

	}
	if (GetKeyState(VK_MBUTTON) & 0x80) {

	}

	//変換行列の更新
	CTransform::Update();
	//UI設定
	CApplication::Ui()->PosY(mPosition.Y());
	CApplication::Ui()->RotX(mRotation.X());
	CApplication::Ui()->RotY(mRotation.Y());


	//重力処理
	mVelocity = mVelocity + GRAVITY;
	//移動量を反映
	mPosition = mPosition + mVelocity;	

	//移動処理
	if (mPosition.Y() > 0.0f) {	//地面に接触していない
		mPosition = mPosition + mVelocity;
		mVelocity = mVelocity + GRAVITY;
	}
	//地面に接触している場合は、位置を地面の上に固定する
	if (mPosition.Y() <= 0.0f) {
		mPosition = CVector(mPosition.X(), 0.0f, mPosition.Z());
		mVelocity = CVector(mVelocity.X(), 0.0f, mVelocity.Z());
	}

	//復活処理に使える
	
	////位置が画面外に出た場合は初期位置に戻す
	//if (mPosition.Y() < -10.0f)
	//{
	//	mPosition = CVector(0.0f, 0.0f, 0.0f);
	//	mVelocity = CVector(0.0f, 0.0f, 0.0f);
	//}
}

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
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				mVelocity = CVector(0.0f, 0.0f, 0.0f);

				//行列の更新
				CTransform::Update();
			}
			else
			{
				//重力処理
				mVelocity =  GRAVITY;
			}
		}
		break;
	}
}