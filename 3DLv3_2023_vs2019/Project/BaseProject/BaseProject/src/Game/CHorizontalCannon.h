#ifndef CHORIZONTALCANNON_H
#define CHORIZONTALCANNON_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"

class CPlayer;

// ��C�N���X
class CHorizontalCannon : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CHorizontalCannon(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CHorizontalCannon();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:

	// �v���C���[�������鏈��
	bool IsFoundPlayer() const;

	// ��C���f��
	CModel* mpCannon;

	// ���ɑł܂ł̎��Ԍv��
	float mFireTime;
	// �łĂ邩�ǂ���
	bool mFire;

};

class CCannonFoundationsHorizontal : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCannonFoundationsHorizontal(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CCannonFoundationsHorizontal();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:

	// ��C�̓y�䃂�f��
	CModel* mpCannonFoundations;
	// ��C�̃R���C�_�[
	//CColliderMesh* mpColliderMesh;

};
#endif