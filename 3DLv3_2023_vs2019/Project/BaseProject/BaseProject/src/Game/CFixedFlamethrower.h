#ifndef CFIXEDFLAMETHROWER_H
#define CFIXEDFLAMETHROWER_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderMesh.h"
class CFlamethrower;

// �Œ莮�Ή����ˊ�
class CFixedFlamethrower : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�X�P�[��</param>
	/// <param name="rot">��]</param>
	CFixedFlamethrower(const CVector& pos, const CVector& scale, const CVector& rot);

	// �f�X�g���N�^
	~CFixedFlamethrower();

	/// <summary>
	/// �R���W����
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	//void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	void Update() override;

	void Render() override;

private:

	// ���f���E�f��
	CModel* mpFlamethrowerModel;
	CModel* mpFlamethrowerTank;
	// �Ή����˃G�t�F�N�g
	CFlamethrower* mpFlamethrower;

	// �Ή����ˊ�̃R���C�_�[
	CColliderMesh* mpColliderMesh;

	// ��Ԋ֘A
	// �Ή����ˊ�̏��
	enum class EState
	{
		Idle,
	};
	// ��Ԃ�؂�ւ���
	void ChangeState(EState state);
	void UpdateIdle();
	EState mState;

	// �ϐ��֘A
	int mStateStep;
	bool fire;
	float mWaitTime;

	bool IsFoundPlayer() const;
};
#endif