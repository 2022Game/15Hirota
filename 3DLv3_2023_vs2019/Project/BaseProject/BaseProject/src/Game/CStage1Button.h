#ifndef CSTAGE1BUTTON_H
#define CSTAGE1BUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;
class COperationUI;

// �X�e�[�W1�I���{�^��
class CStage1Button : public CObjectBase
{
public:
	// �R���X�g���N�^
	CStage1Button(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CStage1Button();

	// �C���X�^���X�̃|�C���^�̎擾
	static CStage1Button* Instance();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W��I���������Ƃ�`����
	bool IsStage1Button();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CStage1Button* spInstance;

	// �X�e�[�W1�I���{�^��
	CModel* mpStage1ButtonModel;
	// �X�e�[�W1�I���{�^���R���C�_�[
	CColliderMesh* mpColliderMesh;

	// �G���^�[�L�[��UI�摜
	COperationUI* mpEnter;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	// �o�ߎ���
	float mElapsedTime;
	// �X�e�[�W1�Ɉڍs���邩�ǂ���
	bool mIsStage1Button;
	// �v���C���[���G��Ă��邩�ǂ���
	bool mIsPlayerCollision;
};
#endif