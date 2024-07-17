#ifndef COPERATIONINSTRUCTIONSUI_H
#define COPERATIONINSTRUCTIONSUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

// �������UI�N���X
class COperationInstructionsUI : public CUIBase
{
public:
	// �R���X�g���N�^
	COperationInstructionsUI(std::string path);
	// �f�X�g���N�^
	~COperationInstructionsUI();

	// �^�X�N��؂邷��
	void Kill() override;

	// �摜�̃Z���^�[�T�C�Y��ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �p�X��
	std::string mPath;
	//// UI�摜
	//std::vector<CImage*> mUIimages;
	// TUI�摜
	CImage* mpTUI;
	// ENTERUI�摜
	CImage* mpEnterUI;
	// �o�b�N�摜
	CImage* mpBG;
	struct UIData
	{
		std::string UIName;	// �e�L�X�g��
	};
	static const UIData UI_DATA[];

	// ���S�ʒu�̊���
	CVector2 mCenterRatio;
	// �摜�̃X�P�[���l
	float mScale;
};
#endif