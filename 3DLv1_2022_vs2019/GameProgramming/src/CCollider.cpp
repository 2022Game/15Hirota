#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius) 
	:CCollider()
{
	//親設定
	mpParent = parent;
	//親行列設定
	mpMatrix = matrix;
	//CTransform設定
	mPosition = position;	//位置
	//半径
	mRadius = radius;
	//コリジョンマネージャに追加
	//CCollisionManager::Instance()->Add(this);	削除
}

CCollider::CCollider()
	:mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(ESPHERE)
	, mRadius(0)
{
	//コリジョンマネージャーに追加
	CCollisionManager::Instance()->Add(this);
}

//衝突判定
//Collision(コライダ１、コライダ２)
//return:true(衝突している)false(衝突していない)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - opos;
	//中心の距離が半径の合計より小さいと衝突
	if (m->mRadius + o->mRadius > mpos.Length()) {
		//衝突している
		return true;
	}
	//衝突していない
	return false;
}


//デストラクタ
CCollider::~CCollider() {
	//子リジョンリストから削除
	CCollisionManager::Instance()->Remove(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

CCollider::EType CCollider::Type()
{
	return mType;
}

void CCollider::Render() {
	glPushMatrix();
	//コライダの中心座標を計算
	//自分の中心座標を計算
	CVector pos = mPosition * *mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE赤色設定
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//三角の頂点から線分終点へのベクトル
	CVector v0sv = sv - v[0];
	//三角の頂点から終点へのベクトルを求める
	CVector v0ev = ev - v[0];

	//線分画面と交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差してない
	if (dots * dote >= 0.0f) {
		//衝突してない(調整不要)
		*a = normal * -dots;
	}
	else {
		//終点が裏面
		*a = normal * -dote;
	}
	return true;
}