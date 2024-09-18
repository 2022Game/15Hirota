#ifndef CMAJICSWORD_H
#define CMAJICSWORD_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderLine.h"
#include "CModel.h"

// �}�W�b�N�\�[�h�N���X
class CMajicSword :public CWeapon
{
public:
	CMajicSword();
	~CMajicSword();

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

	// ����̍s����擾
	CMatrix Matrix() const override;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// �}�W�b�N�\�[�h�̃��f��
	CModel* mpSword;
	// �U������p�̃R���C�_�[
	CColliderLine* mpAttackCol;

	const CMatrix* mpSpine1Mtx;
	const CMatrix* mpRightHandMtx;

};
#endif