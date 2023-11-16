#ifndef CGUN_H
#define CGUN_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderLine.h"
#include "CModel.h"

class CGun :public CWeapon
{
public:
	CGun();
	~CGun();

	void Update();
	void Render();

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

private:

	CModel* mpGun;
	// �U������p�̃R���C�_�[
	CColliderLine* mpAttackCol;
};
#endif