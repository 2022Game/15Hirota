#ifndef CSTAGEBUTTON_H
#define CSTAGEBUTTON_H

#include "CColliderMesh.h"
#include "CRideableObject.h"
class CStageMenu;
class CModel;

// �X�e�[�W�I���{�^��
class CStageButton : public CRideableObject
{
public:
	// �R���X�g���N�^
	CStageButton(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CStageButton();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// �X�e�[�W�I���{�^��
	CModel* mpModel;
	// �X�e�[�W�I���{�^���̃R���C�_�[
	CColliderMesh* mpColliderMesh;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	CStageMenu* mpStageMenu;
};
#endif