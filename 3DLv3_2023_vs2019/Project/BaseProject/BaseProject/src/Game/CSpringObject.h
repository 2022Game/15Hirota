#ifndef CSPRINGOBJECT_H
#define CSPRINGOBJECT_H

#include "CModel.h"
#include "CCollider.h"
#include "CObjectBase.h"

class CSpringObject : public CObjectBase
{
public:
	CSpringObject(const CVector& pos, const CVector& scale, const CVector& rot);
	virtual ~CSpringObject();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void Update() override;
	void Render() override;
protected:
	CModel* mpModel;
	CCollider* mpCollider;

	enum class ESpring
	{
		eIdle,
		eSpring
	};
	void ChangeState(ESpring state);

	void UpdateIdle();

	void SpringStart();
	void UpdateSpring();
	ESpring mState;

	// �x�N�g���֘A
	// �����̑傫��
	CVector mStartScale;
	// �k�ޑ傫��
	CVector mShrinkScale;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// SPACE���������Ƃ��̌o�ߎ���
	float mJumpedElapsedTime;
	// �Փ˂��Ă��邩
	bool mIsCollisionPlayer;
};
#endif