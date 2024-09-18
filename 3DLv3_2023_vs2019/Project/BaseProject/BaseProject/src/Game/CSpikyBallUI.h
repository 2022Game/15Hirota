#ifndef CSPIKYBALLUI_H
#define CSPIKYBALLUI_H

#include "CTask.h"
#include <vector>

class CImage;
class CPlayer;

// �Ƃ��{�[���g�p�摜
class CSpikyBallUI : public CTask
{
public:
	// �R���X�g���N�^
	CSpikyBallUI();
	// �f�X�g���N�^
	~CSpikyBallUI();

	// �J��
	void Open();
	// ����
	void Close();

	// �J���Ă��邩�ǂ���
	bool IsOpened() const;

	// �v���C���[�I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��֐�
	void SetPlayer(CPlayer* player);

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	// �g�p�ҋ@���
	void UpdateIdle();
	// �g�p�ςݑҋ@���
	void UpdateUsed();

	enum class EState
	{
		eIdle,	// �g�p�ҋ@���
		eUsed,	// �g�p�ςݑҋ@���
	};
	// ��Ԑ؂�ւ�
	void ChangeState(EState state);

	// �Ƃ��{�[���g�̉摜
	CImage* mpSpikyFrame;
	// �Ƃ��{�[���̉摜
	CImage* mpSpikyBallUI;
	// CTRL�摜
	CImage* mpCTRL;

	// ���݂̏��
	EState mState;
	// �v���C���[�̃|�C���^�[
	CPlayer* mpPlayer;
	// ��ԓ��ł̃X�e�b�v�Ǘ��p
	int mStateStep;
	// �o�ߎ��Ԍv���p
	float mElapsedTime;
	// �J���Ă��邩�ǂ���
	bool mIsOpened;
};
#endif