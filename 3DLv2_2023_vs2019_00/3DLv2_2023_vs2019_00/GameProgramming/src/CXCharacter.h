#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter3.h"

class CXCharacter : public CCharacter3{
public:
	//����������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix& m);
	//�`�揈��
	void Render();
	//�A�j���[�V�����̍Đ��I������
	//true:�I���@false:�Đ���
	bool IsAnimationFinished();
	//�A�j���[�V�����ԍ��̎擾
	int AnimationIndex();
	void CXCharacter::Update();
	//�f�t�H���g�R���X�g���N�^
	CXCharacter();
	virtual~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
protected:
	CModelX* mpModel;	//���f���f�[�^
	CMatrix* mpCombinedMatrix;	//�����s��ޔ�
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame;	//�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;	//�A�j���[�V�����̍Đ��t���[����
};
#endif