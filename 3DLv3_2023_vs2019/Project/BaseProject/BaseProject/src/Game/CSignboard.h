#ifndef CSIGNBOARD_H
#define CSIGNBOARD_H

#include "CColliderMesh.h"
#include "CRideableObject.h"
class CImage;
class CModel;
class CSignboardUI;

// �ŔN���X
class CSignboard : public CRideableObject
{
public:
	// �C���X�^���X�̃|�C���^�̎擾
	static CSignboard* Instance();

	CSignboard(const CVector& position, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CSignboard();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փ˂����Ƃ��̏��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;

	//�v���C���[����������
	bool IsFoundPlayer() const;

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// �v���C���[�̃C���X�^���X
	static CSignboard* spInstance;


	// ���f���E�f�ފ֘A
	// �Ŕ��f��
	CModel* mpModel;
	// �Ŕ��f���̃R���C�_�[
	CColliderMesh* mpColliderMesh;

	// �e�L�X�g�C���[�W
	CImage* mUkyeText;
	// PAUSE�e�L�X�g�̃C���[�W
	CImage* mPauseText;
	// �Ŕ̃e�L�X�g�摜
	CImage* mText;
	// U�L�[�̃e�L�X�g�摜
	CSignboardUI* mpUkye;


	// ��Ԋ֘A
	// �Ŕ̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Appeared,	// ����Ă�����
	};
	// ���݂̏��
	EState mState;


	// �ϐ��֘A
	//�|�[�Y�����ǂ���
	bool mIsPaused;
	//�o�ߎ��Ԍv���p
	float mElapsedTime;
	//PAUSE�e�L�X�g�̃A���t�@�l�ۑ��p
	float mPauseTextAlpha;
	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ETag mReactionTag;
	// �G�ꂽ���ɔ������郌�C���[
	ELayer mReactionLayer;

	

};
#endif