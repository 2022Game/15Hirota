#pragma once
#include "CCollider.h"

/// <summary>
/// �����R���C�_�[
/// </summary>
class CColliderLine : public CCollider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�����̎n�_</param>
	/// <param name="v1">�����̏I�_</param>
	CColliderLine(CObjectBase* owner, ELayer layer,
		const CVector& v0, const CVector& v1);

	/// <summary>
	/// �����R���C�_�[�̐ݒ�
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�����̎n�_</param>
	/// <param name="v1">�����̏I�_</param>
	void Set(CObjectBase* owner, ELayer layer,
		const CVector& v0, const CVector& v1);

	/// <summary>
	/// ���_�擾
	/// </summary>
	/// <param name="index">�C���f�b�N�X�l</param>
	/// <returns>���_���W</returns>
	CVector V(int index) const;
	float Radius() const;

	// �R���C�_�[�`��
	void Render();

private:
	CVector mV[2];	// �����̒��_�̔z��
	float mRadius;
};