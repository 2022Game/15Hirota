#ifndef CMEDALOBJECTBASE_H
#define CMEDALOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

class CMedalObjectBase : public CObjectBase
{
public:
	CMedalObjectBase(ETaskPriority prio = ETaskPriority::eMedal);
	virtual ~CMedalObjectBase();
	// ���_���擾
	virtual void MedalStart();
	// ���_���擾�I��
	virtual void MedalEnd();
protected:
	// ���_�����q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitMedalObj(CObjectBase* obj);
	// ���łɃ��_���Ƀq�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttachHitMedalObj(CObjectBase* obj) const;

	// ���_���A�C�e���q�b�g�ς݂̃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mMedalObjects;
};
#endif