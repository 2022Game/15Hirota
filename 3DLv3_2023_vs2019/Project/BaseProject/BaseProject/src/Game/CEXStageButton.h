#ifndef CEXSTAGEBUTTON_H
#define CEXSTAGEBUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;
class COperationUI;

// EX�X�e�[�W�I���{�^��
class CEXStageButton : public CObjectBase
{
public:
	// �R���X�g���N�^
	CEXStageButton(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CEXStageButton();

	// �C���X�^���X�̃|�C���^�̎擾
	static CEXStageButton* Instance();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W��I���������Ƃ�`����
	bool IsEXStageButton();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CEXStageButton* spInstance;

	// EX�X�e�[�W�I���{�^��
	CModel* mpEXStageButtonModel;
	// EX�X�e�[�W�I���{�^���R���C�_�[
	CColliderMesh* mpColliderMesh;

	// �G���^�[�L�[��UI�摜
	COperationUI* mpEnter;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	// �o�ߎ���
	float mElapsedTime;
	// EX�X�e�[�W�Ɉڍs���邩�ǂ���
	bool mIsEXStageButton;
	// �v���C���[���G��Ă��邩�ǂ���
	bool mIsPlayerCollision;
};
#endif