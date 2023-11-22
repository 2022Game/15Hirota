#ifndef CBulletEffectEFFECT_H
#define CBulletEffectEFFECT_H

#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CEffect.h"
#include "CBillBoard.h"

class CBulletEffect :public CBillBoard
{
public:
	CBulletEffect();
	~CBulletEffect();

	//CMatrix Matrix() const override;

	void Update();
	void Render();
private:
	// �e�ۂ̈ړ�����
	float mMoveDistance;
	// �e�̃G�t�F�N�g
	static CEffect* mpBulletEffect;

	const CMatrix* mpAttachMtx;

	CVector mPos;
};
#endif