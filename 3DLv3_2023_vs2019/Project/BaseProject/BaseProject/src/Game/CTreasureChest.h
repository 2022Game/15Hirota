#ifndef CTREASURECHEST_H
#define CTREASURECHEST_H

#include "CObjectBase.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"

class CModel;
class COperationUI;

// ��
class CTreasureChest : public CObjectBase
{
public:
	CTreasureChest(const CVector& pos,const CVector&scale,const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CTreasureChest();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	void Update() override;
	void Render() override;
private:

	CModel* mpChest;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestCol;

	// �x�N�g���֘A
	// �󔠃��f���̏����ʒu
	CVector mStartPos;


	ETag mReactionTag;
	ELayer mReactionLayer;

};

// �󔠂̊W
class CTreasureChestTwo : public CObjectBase
{
public:
	CTreasureChestTwo(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CTreasureChestTwo();

	void Update() override;
	void Render() override;

private:
	enum class EState
	{
		Idle,
		Two,
		End,
	};
	void UpdateIdle();
	void UpdateTwo();
	void UpdateEnd();
	EState mState;
	void ChangeState(EState state);


	CModel* mpChestTwo;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestTwoCol;

	COperationUI* mpKey;


	// �x�N�g���֘A
	// �󔠃��f���̏����ʒu
	CVector mStartPos;
	// ������]�l
	CQuaternion mDefaultRot;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �҂�����
	float mWaitTime;
	// ��]�J�n���̊p�x
	float mRotateStartAngle;
	// ��]�I�����̊p�x
	float mRotateEndAngle;
	ETag mReactionTag;
	ELayer mReactionLayer;

	bool IsFoundPlayer() const;
};
#endif