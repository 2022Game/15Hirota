#ifndef CTREASURECHEST_H
#define CTREASURECHEST_H
#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"

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
	enum class EState
	{
		Idle,
		GetItem,
	};
	void UpdateIdle();
	void UpdateGetItem();
	EState mState;
	void ChangeState(EState state);


	CModel* mpChest;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestCol;


	// �x�N�g���֘A
	// �󔠃��f���̏����ʒu
	CVector mStartPos;

	// �ϐ��֘A
	// ��ԓ��̃X�e�b�v
	int mStateStep;
	// �҂�����
	float mWaitTime;
	ETag mReactionTag;
	ELayer mReactionLayer;

};

class CTreasureChestTwo : public CObjectBase
{
public:
	CTreasureChestTwo(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CTreasureChestTwo();

	void Update();
	void Render();

private:
	enum class EState
	{
		Idle,
		Two,
	};
	void UpdateIdle();
	void UpdateTwo();
	EState mState;
	void ChangeState(EState state);


	CModel* mpChestTwo;
	CColliderSphere* mpChestSphere;
	CColliderMesh* mpChestTwoCol;


	// �x�N�g���֘A
	// �󔠃��f���̏����ʒu
	CVector mStartPos;

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
};
#endif