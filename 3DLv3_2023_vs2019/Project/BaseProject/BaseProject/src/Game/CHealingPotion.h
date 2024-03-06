#ifndef CHEALINGPOTION_H
#define CHEALINGPOTION_H

#include "CObjectBase.h"
#include "CItemObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSound;
class CPlayer;

// �񕜖�A�C�e���I�u�W�F�̃x�[�X�N���X
class CHealingPotion : public CItemObjectBase
{
public:
	CHealingPotion();
	~CHealingPotion();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	//// �񕜊J�n
	//void HealingStart();
	//// �񕜏I��
	//void HealingEnd();

	void OnTouch(CPlayer* player);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���f���E�f�ފ֘A
	// �񕜖򃂃f��
	CModel* mpHealingPotion;
	// �񕜔���p�̃R���C�_�[
	CColliderSphere* mpHealingCol;

	// �񕜂����Ƃ���SE
	CSound* mpHealingSE;

	// �ړ����x
	CVector mMoveSpeed;

	// �ϐ��֘A
	// �ڒn���Ă��邩
	bool mIsGround;
	// �񕜂������ǂ���
	bool mHealingUsed;
	bool mIsHeld;
};
#endif