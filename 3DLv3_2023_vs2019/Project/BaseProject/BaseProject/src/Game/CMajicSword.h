#ifndef CMAJICSWORD_H
#define CMAJICSWORD_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderLine.h"
#include "CModel.h"

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

	void Update();
	void Render();

private:

	CModel* mpSword;
	// �U������p�̃R���C�_�[
	CColliderLine* mpAttackCol;
};
#endif