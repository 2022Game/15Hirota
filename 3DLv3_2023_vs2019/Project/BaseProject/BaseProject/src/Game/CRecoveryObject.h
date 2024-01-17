#ifndef CRECOVERYOBJECT_H
#define CRECOVERYOBJECT_H
#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSound;

// �񕜃A�C�e��
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

	// �񕜊J�n
	void RecoverStart();
	// �񕜏I��
	void RecoverEnd();

	// �ړ�����
	// ��O
	void MoveFront();
	// ��
	void MoveBack();
	// �E
	void MoveLight();
	// ��
	void MoveReft();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

	// �񕜃A�C�e���̍s����擾
	//CMatrix Matrix() const override;

private:
	//// ���f���E�f�ފ֘A /////////////////////////
	
	// �񕜃��f��
	CModel* mpRecoverModel;
	// �񕜔���p�̃R���C�_�[
	CColliderSphere* mpRecoverCol;

	// �񕜂����Ƃ���SE
	CSound* mpRecoberSE;

	/////////////////////////////////////////


	//// �x�N�g���֘A ///////////////////////
	
	// �ړ�����
	CVector mMoveVector;
	// �ړ����x
	CVector mMoveSpeed;
	// �������
	CVector mTargetDir;

	/////////////////////////////////////////

	//// �ϐ��֘A ///////////////////////////

	// �J�E���g
	int mSwitchCounter;
	// �v������
	float mElapsedTime;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
	// �񕜂������ǂ���
	bool mRecoveryUsed;

	//////////////////////////////////////////
};
#endif