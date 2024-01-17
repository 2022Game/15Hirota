#ifndef CINVINCIBLEOBJECTBASE_H
#define CINVINCIBLEOBJECTBASE_H
#include "CObjectBase.h"
class CCharaBase;

class CInvincibleObjectBase : public CObjectBase
{
public:
	CInvincibleObjectBase();
	virtual ~CInvincibleObjectBase();


	// ���G�J�n
	virtual void InvincibleStart();
	// ���G�I��
	virtual void InvincibleEnd();

protected:
	// ���G�A�C�e�����q�b�g�����I�u�W�F�N�g��ǉ�
	void AddAttachHitObjInvincible(CObjectBase* obj);
	// ���łɖ��G�A�C�e�����q�b�g���Ă���I�u�W�F�N�g���ǂ���
	bool IsAttachHitObjInvincible(CObjectBase* obj) const;

	// ���G�A�C�e���Ƀq�b�g�ς݃I�u�W�F�N�g���X�g
	std::list<CObjectBase*> mInvincible;
};
#endif