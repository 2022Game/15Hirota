#ifndef CRECOVERYOBJECT_H
#define CRECOVERYOBJECT_H
#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"

class CRecoveryObject : public CItemObjectBase
{
public:
	CRecoveryObject();
	~CRecoveryObject();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂����Ƃ��̏��</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//// �񕜊J�n
	//void RecoverStart();

	//void RecoverEnd();

	// �񕜃A�C�e���̍s����擾
	//CMatrix Matrix() const override;

	void Update();
	void Render();

	void Move();	// ��O
	void MoveZ();	// ��
	void MoveX();	// �E
	void MoveY();	// ��

private:
	CModel* mpRecoverModel;
	// �񕜔���p�̃R���C�_�[
	CColliderSphere* mpRecoverCol;

	CVector moveVector;
	CVector mMoveSpeed;
	CVector mTargetDir;

	float mElapsedTime;

	bool mIsGround;

	int mSwitchCounter;

	bool mIsEnabled;

	bool mRecoveryUsed;
};
#endif