#ifndef CALWAYSVERTICALNEEDLE_H
#define CALWAYSVERTICALNEEDLE_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CModel.h"

// �펞�o�Ă���j�N���X
class CAlwaysVerticalNeedle : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CAlwaysVerticalNeedle(const CVector& pos, const CVector& scale, const CVector& rot);

	// �f�X�g���N�^
	~CAlwaysVerticalNeedle();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �펞�o�Ă���j���f��
	CModel* mpNeedleBase;
	// �펞�o�Ă���j���f���̃R���C�_�[
	CColliderMesh* mpNeedleBaseCol;
	// �펞�o�Ă���j���f���̐j�R���C�_�[
	CColliderMesh* mpNeedleCol;

	// �U����̍ċN����
	float mWaitAttackTime;
	// �Փ˂��Ă��邩
	bool mIsCollision;
	// �v���C���[���U��������
	bool mIsAttack;
};
#endif