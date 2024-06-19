#ifndef CELECTRICLASER_H
#define CELECTRICLASER_H

#include "CObjectBase.h"
#include "CTexture.h"
#include "CColliderLine.h"

class CLineEffect;

// 電流ギミック
class CElectricLaser : public CObjectBase
{
public:
	CElectricLaser(const CVector& pos, const CVector& move, float moveTime, 
		const CVector& laserStartPos, const CVector& laserEndPos);
	~CElectricLaser();

	void DeleteObject(CObjectBase* obj) override;

	void Update() override;

private:
	CLineEffect* mpLineEffect;
	TexAnimData mEffectAnimData;

	CColliderLine* mpLine;

	CVector mStartPos;
	CVector mMoveVec;
	float mMoveTime;
	float mElapsedTime;
};
#endif