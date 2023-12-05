#ifndef CKICK_H
#define CKICK_H
#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CColliderSphere.h"
#include "CModel.h"

class CKick :public CEnemyWeapon
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

	// ����̍s����擾
	CMatrix Matrix() const override;

	void Update();
	void Render();

private:
	// �U������p�̃R���C�_�[
	CColliderSphere* mpAttackCol;
};
#endif