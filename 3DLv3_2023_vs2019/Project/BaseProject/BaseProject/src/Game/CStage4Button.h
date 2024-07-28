#ifndef CSTAGE4BUTTON_H
#define CSTAGE4BUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;
class COperationUI;

// �X�e�[�W4�I���{�^��
class CStage4Button : public CObjectBase
{
public:
	CStage4Button(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CStage4Button();

	// �C���X�^���X�̃|�C���^�̎擾
	static CStage4Button* Instance();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W��I���������Ƃ�`����
	bool IsStage4Button();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CStage4Button* spInstance;

	// �X�e�[�W4�I���{�^��
	CModel* mpStage4ButtonModel;
	// �X�e�[�W4�I���{�^��
	CColliderMesh* mpColliderMesh;

	// �G���^�[�L�[��UI�摜
	COperationUI* mpEnter;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	// �o�ߎ���
	float mElapsedTime;
	// �X�e�[�W4�Ɉڍs���邩�ǂ���
	bool mIsStage4Button;
	// �v���C���[���G��Ă��邩�ǂ���
	bool mIsPlayerCollision;
};
#endif