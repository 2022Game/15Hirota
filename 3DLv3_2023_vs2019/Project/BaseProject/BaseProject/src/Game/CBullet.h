#ifndef CBULLET_H
#define CBULLET_H
#include "CObjectBase.h"
#include "CEnemyWeapon.h"
#include "CColliderSphere.h"
#include "CModel.h"
#include "CEffect.h"

class CBullet :public CEnemyWeapon
{
public:
	CBullet();
	~CBullet();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// ����̍s����擾
	CMatrix Matrix() const override;

	// �U���J�n
	void AttackStart() override;

	// �U���I��
	void AttackEnd() override;

	void Update();
	void Render();
private:
	static CModel* mpBullet;
	// �U������p�̃R���C�_�[
	CColliderSphere* mpAttackCol;

	// �e�ۂ̈ړ�����
	float mMoveDistance;
	// �e�̃G�t�F�N�g
	CEffect* mpBulletEffect;

	CVector mPos;
};
#endif