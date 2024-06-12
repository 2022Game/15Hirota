#ifndef CMEATOBJECTBASE_H
#define CMEATOBJECTBASE_H

#include "CObjectBase.h"

class CCharaBase;

// �I�u�W�F�N�g�p��
// ���A�C�e���I�u�W�F�̃N���X
class CMeatObjectBase : public CObjectBase
{
public:
	CMeatObjectBase();
	virtual ~CMeatObjectBase();

	// �i���o�[��ݒ�
	void SetMeatNumber(int number);
	// �i���o�[���擾
	int GetMeatNumber() const;

private:
	int mNumber;
};
#endif