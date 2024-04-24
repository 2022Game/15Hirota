#ifndef CSCREENITEM_H
#define CSCREENITEM_H

#include "CTask.h"
#include <utility>
#include <vector>
class CPlayer;
class CImage;

// ��ʏ�̃C���x���g���A�C�e���N���X
class CScreenItem : public CTask
{
public:
	CScreenItem();
	~CScreenItem();

	void Open();
	void Close();
	bool IsOpened() const;

	void Decide(int select);

	void Update() override;
	void Render() override;

	// �v���C���[�I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��֐�
	void SetPlayer(CPlayer* player);

private:
	// �g�g�݂̉摜
	CImage* mpBackground;
	bool mIsOpened;
	// �A�C�e���̎��
	enum PlayerItem
	{
		NONE,
		INVINCIBLE_ITEM,	// �����A�C�e���������Ă��Ȃ�
		HEALING_ITEM,		// ���G�A�C�e��
		ATTACK_UP_ITEM,		// �񕜃A�C�e��
		DEFENSE_ITEM,		// �U���̓A�b�v�A�C�e��
	};
	// �A�C�e���̎�ނƁA�A�C�e���̉摜���Ǘ�
	std::vector<std::pair<PlayerItem, CImage*>> mPlayerItems;
	// �A�C�e���������ꍇ�̉摜
	std::vector<std::pair<PlayerItem, CImage*>> mNoItems;
	// �ԍ��̉摜
	std::vector<CImage*> mNumberItems;

	CPlayer* mPlayer;
};
#endif