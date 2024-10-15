#ifndef CCANNONBASE_H
#define CCANNONBASE_H

#include "CObjectBase.h"
#include "CModel.h"

class CPlayer;

// ��C�N���X
class CCannonBase : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCannonBase(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	virtual ~CCannonBase();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="other">�Փ˂������g�̃R���C�_�[</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	virtual void Update() override;
	// �`�揈��
	void Render() override;

protected:

	// �v���C���[�������鏈��
	bool IsFoundPlayer() const;

	// ��C���f��
	CModel* mpCannon;
	// �ŏ��Ɍ����Ă������
	CVector InitialVectorZ;
};

class CCannonFoundationsBase : public CObjectBase
{
public:
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCannonFoundationsBase(const CVector& pos, const CVector& scale, const CVector& rot,
		std::string modelPath = "CannonFound");
	// �f�X�g���N�^
	~CCannonFoundationsBase();

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

protected:

	// ��C�̓y�䃂�f��
	CModel* mpFoundations;
};
#endif