#pragma once
#include "CCollider.h"

/// <summary>
/// �O�p�`�R���C�_�[
/// </summary>
class CColliderTriangle : public CCollider
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�O�p�`�̒��_ 0</param>
	/// <param name="v1">�O�p�`�̒��_ 1</param>
	/// <param name="v2">�O�p�`�̒��_ 2</param>
	CColliderTriangle(CObjectBase* owner, ELayer layer,
		const CVector& v0, const CVector& v1, const CVector& v2);
	// �R���X�g���N�^�i�����Ȃ��Łj
	CColliderTriangle();

	/// <summary>
	/// �O�p�`�R���C�_�[�̐ݒ�
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	/// <param name="v0">�O�p�`�̒��_ 0</param>
	/// <param name="v1">�O�p�`�̒��_ 1</param>
	/// <param name="v2">�O�p�`�̒��_ 2</param>
	void Set(CObjectBase* owner, ELayer layer,
		const CVector& v0, const CVector& v1, const CVector& v2);

	CVector V(int index) const;

	// �R���C�_�[�`��
	void Render();

private:
	CVector mV[3];	// �O�p�`�̒��_�̔z��
};