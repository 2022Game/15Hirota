#ifndef CSTAGE3BUTTON_H
#define CSTAGE3BUTTON_H

#include "CColliderMesh.h"
#include "CObjectBase.h"

class CModel;

// �X�e�[�W3�I���{�^��
class CStage3Button : public CObjectBase
{
public:
	// �R���X�g���N�^
	CStage3Button(const CVector& pos, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	// �f�X�g���N�^
	~CStage3Button();

	// �C���X�^���X�̃|�C���^�̎擾
	static CStage3Button* Instance();

	// �Փˏ���
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	// �X�e�[�W��I���������Ƃ�`����
	bool IsStage3Button();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �C���X�^���X
	static CStage3Button* spInstance;

	// �X�e�[�W1�I���{�^��
	CModel* mpStage3ButtonModel;
	// �X�e�[�W1�I���{�^��
	CColliderMesh* mpColliderMesh;

	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	float mElapsedTime;
	bool mIsStage3Button;
};
#endif