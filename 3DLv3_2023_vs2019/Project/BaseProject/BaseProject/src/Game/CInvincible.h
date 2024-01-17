#ifndef CINVINCIBLE_H
#define CINVINCIBLE_H

#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"

// ���G�A�C�e��
class CInvincible : public CItemObjectBase
{
public:
	CInvincible();
	~CInvincible();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂����Ƃ��̏��</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

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


	// ���G�I�u�W�F�̍s����擾
	//CMatrix Matrix() const override;

private:
	//// ���f���֘A/////////////////////////////
	
	// ���G�A�C�e���̃��f��
	CModel* mpRecoverModel;
	// ���G�A�C�e���̃R���C�_�[
	CColliderSphere* mpRecoverCol;

	////////////////////////////////////////////


	//// �x�N�g���֘A //////////////////////////

	// �ړ�����
	CVector mMoveVector;
	// �ړ����x
	CVector mMoveSpeed;
	// �������
	CVector mTargetDir;

	/////////////////////////////////////////////


	//// �ϐ��֘A ///////////////////////////////

	// �J�E���g
	int mSwitchCounter;
	// �v�����ԏ���
	float mElapsedTime;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
	// ���G�ɂȂ������ǂ���
	bool mRecoveryUsed;

	/////////////////////////////////////////////
};
#endif