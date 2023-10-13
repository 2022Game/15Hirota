#pragma once
#include "CCollider.h"

/// <summary>
/// ���R���C�_�[
/// </summary>
class CColliderSphere : public CCollider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="radius">���̔��a</param>
	CColliderSphere(CObjectBase* owner, ELayer layer, float radius);

	/// <summary>
	/// ���R���C�_�[�̐ݒ�
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="radius">���̔��a</param>
	void Set(CObjectBase* owner, ELayer layer, float radius);

	/// <summary>
	/// ���̍��W�Ɣ��a���擾
	/// </summary>
	/// <param name="pos">���̍��W</param>
	/// <param name="rad">���̔��a</param>
	void Get(CVector* pos, float* rad) const;

	// �R���C�_�[�`��
	void Render();

private:
	float mRadius;	// ���̔��a
};
