#ifndef CSIKAKU_H
#define CSIKAKU_H

#include "CCharacter3.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CColliderMesh.h"
#include "CColliderTriangle.h"
#include "CPlayer.h"

/*
エネミーとキャラクタクラスを継承
*/
class CSikaku :public CCharacter3 {
private:
	//コライダ
	CColliderMesh mColliderMesh1;
protected:
	
public:
	//static int mD;
	//衝突処理
	//Collision(コライダ１、コライダ２）
	void Collision(CCollider* m, CCollider* o);

	void Collision();
	//コンストラクタ
	//CEnemy(モデル,位置,回転,拡縮）
	CSikaku(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	~CSikaku();

	/*bool IsPlayerOnTop() const;*/

	//更新処理
	void Update();
};
#endif