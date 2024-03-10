#ifndef CINVENTORY_H
#define CINVENTORY_H

#include "CTask.h"
#include "CImage.h"
#include "CPlayer.h"
#include <utility>
#include <vector>
class CPlayer;

// �C���x���g���̃A�C�e���Ǘ��N���X
class CInventoryMenu : public CTask
{
public:
	CInventoryMenu();
	~CInventoryMenu();

	void Open();
	void Close();
	bool IsOpened() const;

	void Decide(int select);

	void Update() override;
	void Render() override;

	// �v���C���[�I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��֐�
	void SetPlayer(CPlayer* player);

private:
	// �w�i�̉摜
	CImage* mpBackground;
	// �I���A�C�e���̃t���[��
	CImage* mpSelectFrame;
	int mSelectIndex;
	bool mIsOpened;
	// �A�C�e���̎��
	enum PlayerItem 
	{
		NONE,				// �����A�C�e���������Ă��Ȃ�
		INVINCIBLE_ITEM,	// ���G�A�C�e��
		HEALING_ITEM,		// �񕜃A�C�e��
		ATTACK_UP_ITEM,		// �U���̓A�b�v�A�C�e��
		DEFENSE_ITEM,		// �h��̓A�b�v�A�C�e��
		// ���̃A�C�e�����ǉ��\
	};
	// �A�C�e���̎�ނƁA�A�C�e���̉摜���Ǘ�
	// ���G�A�C�e���̉摜
	// �񕜃A�C�e���̉摜
	std::vector<std::pair<PlayerItem, CImage*>> mPlayerItems;
	// �A�C�e���������ꍇ�̉摜
	std::vector<std::pair<PlayerItem, CImage*>> mNoItems;
	// �A�C�e�����I���\��
	bool CInventoryMenu::IsValidSelection(int index);

	CPlayer* mPlayer;
};
#endif