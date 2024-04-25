#ifndef CKICK_H
#define CKICK_H
#include "CObjectBase.h"
#include "CWeaponEnemy.h"
#include "CColliderSphere.h"
#include "CXCharacter.h"
class CModel;

// ���̃R���C�_�[�N���X
class CKick :public CWeaponEnemy
{
public:
	CKick();
	~CKick();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �U���J�n
	void AttackStart() override;

	// �U���I��
	void AttackEnd() override;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���f���f�[�^
	CModelX* mpModel;
	// �U������p�̃R���C�_�[
	CColliderSphere* mpAttackCol;

	// ��������s��̃|�C���^�[
	const CMatrix* mpAttachMtx;
	// ��������s��̖{��
	CMatrix mAttachMtx;
};
#endif