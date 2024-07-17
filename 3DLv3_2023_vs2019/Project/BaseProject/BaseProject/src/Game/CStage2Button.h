#ifndef CSTAGE2BUTTON_H
#define CSTAGE2BUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;
class COperationUI;

// �X�e�[�W2�I���{�^��
class CStage2Button : public CObjectBase
{
public:
	// �R���X�g���N�^
	CStage2Button(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CStage2Button();

	// �C���X�^���X�̃|�C���^�̎擾
	static CStage2Button* Instance();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W��I���������Ƃ�`����
	bool IsStage2Button();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CStage2Button* spInstance;

	// �X�e�[�W2�I���{�^��
	CModel* mpStage2ButtonModel;
	// �X�e�[�W2�I���{�^���R���C�_�[
	CColliderMesh* mpColliderMesh;

	// �G���^�[�L�[��UI�摜
	COperationUI* mpEnter;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	// �v������
	float mElapsedTime;
	// �X�e�[�W2�Ɉڍs���邩
	bool mIsStage2Button;
	// �v���C���[���G��Ă��邩
	bool mIsPlayerCollision;
};
#endif