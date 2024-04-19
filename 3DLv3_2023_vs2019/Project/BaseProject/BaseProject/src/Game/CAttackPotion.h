#ifndef CATTACKPOTION_H
#define CATTACKPOTION_H

#include "CObjectBase.h"
#include "CAttackObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSound;
class CPlayer;

// �U���̓A�b�v�|�[�V����
// �|�[�V������mtl�ɂ�Textures/��擪�ɓ����
class CAttackPotion : public CAttackObjectBase
{
public:
	CAttackPotion();
	~CAttackPotion();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();
private:
	 
	void UpdateGet();

	// ���f���E�f�ފ֘A
	CModel* mpAttackPotion;
	// �R���C�_�[
	CColliderSphere* mpFieldCol;
	CColliderSphere* mpAttackCol;


	// �x�N�g���֘A
	// �ړ�����
	CVector mMoveVector;
	// �ړ����x
	CVector mMoveSpeed;
	// �������
	CVector mTargetDir;
	CVector mStartPos;


	// �ϐ��֘A
	// �v�����ԏ���
	float mElapsedTime;
	// ���ɐڒn���Ă��邩
	bool mIsGround;
	// ���G�ɂȂ������ǂ���
	bool mAttackUsed;
	// �ێ�����Ă��邩
	bool mIsHeld;

};
#endif