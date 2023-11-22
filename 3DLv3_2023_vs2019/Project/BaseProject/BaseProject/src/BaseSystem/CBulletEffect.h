#ifndef CBulletEffectEFFECT_H
#define CBulletEffectEFFECT_H

#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CEffect.h"
#include "CBillBoard.h"
class CBullet;

class CBulletEffect :public CEffect
{
public:
	CBulletEffect();
	~CBulletEffect();

	//CMatrix Matrix() const override;

	void SetAssociatedBullet(CBullet* pBullet);

	void Update() override;
	void Render() override;
private:
	// �e�ۂ̈ړ�����
	float mMoveDistance;
	// �e�̃G�t�F�N�g
	static CEffect* mpBulletEffect;

	CVector mPos;

	CBullet* mpAssociatedBullet;
};
#endif