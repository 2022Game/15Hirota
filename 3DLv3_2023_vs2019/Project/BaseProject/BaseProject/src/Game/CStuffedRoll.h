#ifndef CSTUFFEDROLL_H
#define CSTUFFEDROLL_H

#include "CTask.h"

class CText;
class CImage;
class CFont;

// �X�^�b�t���[���N���X
class CStuffedRoll : public CTask
{
public:
	// �R���X�g���N�^
	CStuffedRoll();
	// �f�X�g���N�^
	~CStuffedRoll();

	// �C���X�^���X�̃|�C���^�擾
	static CStuffedRoll* Instance();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
private:
	
	// �C���X�^���X
	static CStuffedRoll* spInstance;

	// �e�L�X�g���ړ������鏈��
	void ScrollTextUp(CText* pText, float& yPos, float speed);

	// �t�H���g�e�L�X�g
	CFont* mpFont;
	// �e�L�X�g
	std::vector<CText*> mStuffedRolls;
	std::vector<float> mTextYPositions;

	struct StafData
	{
		std::string stuffName;
		float startTime;
	};
	static const StafData STAFF_DATA[];

	float mStaffRollTime;
};
#endif