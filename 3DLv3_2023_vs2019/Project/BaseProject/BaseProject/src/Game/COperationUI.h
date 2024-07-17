#ifndef COPERATIONUI_H
#define COPERATIONUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

// �������UI�N���X
class COperationUI : public CUIBase
{
public:
	// �R���X�g���N�^
	COperationUI(std::string path);
	// �f�X�g���N�^
	~COperationUI();

	// �^�X�N��؂邷��
	void Kill() override;

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �L�[�摜
	CImage* mpKay;
	// �o�b�N�摜
	CImage* mpBG;

	// �摜�̃X�P�[���l
	float mScale;
};
#endif