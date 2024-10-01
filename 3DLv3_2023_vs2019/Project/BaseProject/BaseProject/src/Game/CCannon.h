#ifndef CCANNON_H
#define CCANNON_H

#include "CObjectBase.h"
#include "CModel.h"
#include "CColliderSphere.h"

class CPlayer;

// ��C�N���X
class CCannon : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCannon(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CCannon();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:

	// �v���C���[�������鏈��
	bool IsFoundPlayer() const;

	// ��C���f��
	CModel* mpCannon;
	// ��C�̃R���C�_�[
	//CColliderMesh* mpColliderMesh;

	// ���ɑł܂ł̎��Ԍv��
	float mFireTime;
	// �łĂ邩�ǂ���
	bool mFire;

};

class CCannonFoundations : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCannonFoundations(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CCannonFoundations();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:

	// ��C�̓y�䃂�f��
	CModel* mpCannonFoundations;
	// ��C�̃R���C�_�[
	//CColliderMesh* mpColliderMesh;

};
#endif