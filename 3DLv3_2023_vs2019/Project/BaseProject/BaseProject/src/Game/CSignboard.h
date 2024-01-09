#ifndef CSIGNBOARD_H
#define CSIGNBOARD_H

#include "CModel.h"
#include "CColliderMesh.h"
#include "CRideableObject.h"
#include "CSignboardUI.h"
class CImage;

class CSignboard : public CRideableObject
{
public:
	//�C���X�^���X�̃|�C���^�̎擾
	static CSignboard* Instance();

	CSignboard(const CVector& position, const CVector& scale, const CVector& rot,
		ETag reactionTag, ELayer reactionLayer);
	~CSignboard();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit) override;
	bool IsFoundPlayer() const;	//�v���C���[����������

	void Update();
	void Render();

private:
	// �v���C���[�̃C���X�^���X
	static CSignboard* spInstance;
	// �\���摜�̏��
	enum class EState
	{
		Idle,		// �ҋ@���
		Appeared,	// ����Ă�����
	};
	//// ��Ԃ�؂�ւ���
	//void ChangeState(EState state);
	//// �ҋ@���
	//void UpdateIdle();
	//// ����Ă�����
	//void UpdateAppeared();

	CImage* mUkyeText;		// �e�L�X�g�C���[�W
	CImage* mPauseText;		// PAUSE�e�L�X�g�̃C���[�W
	CImage* mText;			// �Ŕ̃e�L�X�g�摜


	CModel* mpModel;
	CColliderMesh* mpColliderMesh;

	EState mState;
	int mStateStep;
	int mPauseStep;

	ETag mReactionTag;	// �G�ꂽ���ɔ�������I�u�W�F�N�g�̃^�O
	ELayer mReactionLayer;	// �G�ꂽ���ɔ������郌�C���[

	
	bool mIsPaused;			//�|�[�Y�����ǂ���

	float mElapsedTime;		//�o�ߎ��Ԍv���p
	float mPauseTextAlpha;	//PAUSE�e�L�X�g�̃A���t�@�l�ۑ��p

	CSignboardUI* mpUkye;

};
#endif