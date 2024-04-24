#include "CInventoryMenu.h"
#include "CInput.h"
#include "CImage.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CPlayer.h"


//new CImage("UI\\Item\\Invincible Item.png", ETaskPriority::eUI, 0, ETaskPauseType::eMenu, false, false);
//new CImage("UI\\Item\\Health Recovery Items.png", ETaskPriority::eUI, 0, ETaskPauseType::eMenu, false, false);
//new CImage("UI\\Item\\Increase Attack Power.png", ETaskPriority::eUI, 0, ETaskPauseType::eMenu, false, false);
//new CImage("UI\\Item\\NoItemUI.png", ETaskPriority::eUI, 0, ETaskPauseType::eMenu, false, false);

#define MENU_ALPHA 0.75f

CInventoryMenu::CInventoryMenu()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mIsOpened(false)
	, mPlayer(nullptr)
{
	mpBackground = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);

	// �A�C�e���������Ă��Ȃ��Ƃ��̉摜
	int menuItemCount = 3;
	float spaceY = (float)WINDOW_HEIGHT / (menuItemCount + 1);
	for (int i = 0; i < menuItemCount; i++)
	{
		CImage* item = new CImage
		(
			"UI\\Item\\NoItemUI.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = (1280.0f - 1024.0f + item->GetSize().X()) * 0.5f + 100.0f;
		item->SetPos(posX, spaceY * (i + 1));
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mNoItems.push_back(std::make_pair(PlayerItem::NONE, item));
	}

	int ItemCount = 3;
	float invinciblePosY = spaceY * 1; // �ォ��1�Ԗڂ̈ʒu
	float healingPosY = spaceY * 2; // �ォ��2�Ԗڂ̈ʒu
	float attackPotionPosY = spaceY * 3;
	for (int i = 0; i < ItemCount; i++)
	{
		// ���G�A�C�e��
		CImage* invincible = new CImage
		(
			"UI\\Item\\Invincible Item.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		invincible->SetCenter(invincible->GetSize() * 0.5f);
		float invinciblePosX = (1280.0f - 1024.0f + invincible->GetSize().X()) * 0.5f + 100.0f;
		invincible->SetPos(invinciblePosX, invinciblePosY);
		invincible->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(PlayerItem::INVINCIBLE_ITEM, invincible));

		// �񕜃A�C�e��
		CImage* healing = new CImage
		(
			"UI\\Item\\ScreenItems(Healing).png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		healing->SetCenter(healing->GetSize() * 0.5f);
		float healingPosX = (1280.0f - 1024.0f + healing->GetSize().X()) * 0.5f + 100.0f;
		healing->SetPos(healingPosX, healingPosY);
		healing->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(PlayerItem::HEALING_ITEM, healing));

		// �U���̓A�b�v�A�C�e��
		CImage* attackPotion = new CImage
		(
			"UI\\Item\\ScreenItems(Attack).png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		attackPotion->SetCenter(attackPotion->GetSize() * 0.5f);
		float attackPotionPosX = (1280.0f - 1034.0f + attackPotion->GetSize().X()) * 0.5f + 100.0f;
		attackPotion->SetPos(attackPotionPosX, attackPotionPosY);
		attackPotion->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(PlayerItem::ATTACK_UP_ITEM, attackPotion));
	}

	// �A�C�e���̘g�摜
	mpSelectFrame = new CImage
	(
		"UI/menu_item_select.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpSelectFrame->SetCenter(mpSelectFrame->GetSize() * 0.5f);
	mpSelectFrame->SetColor(1.0f, 0.5f, 0.0f, MENU_ALPHA);

	SetEnable(false);
	SetShow(false);
}

CInventoryMenu::~CInventoryMenu()
{
}

void CInventoryMenu::Open()
{
	// ���ɊJ���Ă�����A�������Ȃ�
	if (mIsOpened) return;

	mIsOpened = true;
	SetEnable(true);
	SetShow(true);

	CPlayer* player = CPlayer::Instance();
	// ���݂̃A�C�e���̐����擾
	int numItems = mPlayerItems.size();

	// �v���C���[���A�C�e���������Ă���ꍇ
	if (numItems > 0) {
		bool itemSelected = false;
		// �ŏ��̃A�C�e����I����Ԃɂ���imSelectIndex��0�ɐݒ�j
		// �v���C���[���A�C�e���������Ă��Ȃ��ꍇ��0�ɐݒ�
		mSelectIndex = 0;
		for (int i = 0; i < mPlayerItems.size(); ++i) {
			// �A�C�e�����v���C���[�������Ă��邩�ǂ������m�F
			if (IsValidSelection(i)) {
				mSelectIndex = i;
				itemSelected = true;
				break;
			}
		}
	}

	// �A�C�e���������Ă��Ȃ��Ƃ��̏���
	bool noitemselect = !mNoItems.size();
	if (noitemselect)
	{
		mSelectIndex = 0;
	}

	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

void CInventoryMenu::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	mIsOpened = false;
	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O������
	mIsOpened = false;
}

bool CInventoryMenu::IsOpened() const
{
	return mIsOpened;
}

void CInventoryMenu::Decide(int select)
{
	CPlayer* player = CPlayer::Instance();
	PlayerItem selectedItem = mPlayerItems[select].first;
	switch (selectedItem)
	{
	case PlayerItem::NONE:
		Close();
		break;
		// ���G�A�C�e�����擾�����Ƃ��̏���
	case PlayerItem::INVINCIBLE_ITEM:
		player->UseInvincibleItem();
		break;
		// �񕜃A�C�e�����擾�����Ƃ��̏���
	case PlayerItem::HEALING_ITEM:
		player->UseHealingItem();
		break;
	case PlayerItem::ATTACK_UP_ITEM:
		player->UseAttackPotion();
		break;
	case PlayerItem::DEFENSE_ITEM:
		break;
	}

	Close();
}

void CInventoryMenu::Update()
{
	bool PlayerHasItem = !mPlayerItems.empty();
	bool NoItemExists = !mNoItems.empty();
	CPlayer* player = CPlayer::Instance();


	int ItemCount = mPlayerItems.size();
	// ���݂̃A�C�e���̐����J�E���g
	int CurrentItemCount = 0;
	// ���ݎ����Ă���A�C�e���̐��𐔂���
	for (int i = 0; i < ItemCount; ++i) {
		if (IsValidSelection(i)) {
			CurrentItemCount++;
		}
	}

	// ��L�[�������ꂽ�ꍇ
	int NewIndex = mSelectIndex;
	// �A�C�e�����I���\���ǂ���
	bool FoundValidItem = false;
	if (CInput::PushKey(VK_UP)) {
		while (!FoundValidItem) {
			NewIndex = (NewIndex + ItemCount - 1) % ItemCount;
			if (IsValidSelection(NewIndex)) {
				FoundValidItem = true;
			}
			if (NewIndex == mSelectIndex) {
				// �I���C���f�b�N�X���ŏ��̈ʒu�ɖ߂����ꍇ�A���[�v�𔲂���
				break;
			}
		}
		if (FoundValidItem) {
			mSelectIndex = NewIndex;
		}
	}
	else if (CInput::PushKey(VK_DOWN)) {
		while (!FoundValidItem) {
			NewIndex = (NewIndex + 1) % ItemCount;
			if (IsValidSelection(NewIndex)) {
				FoundValidItem = true;
			}
			if (NewIndex == mSelectIndex) {
				// �I���C���f�b�N�X���Ō�̈ʒu�ɖ߂����ꍇ�A���[�v�𔲂���
				break;
			}
		}
		if (FoundValidItem) {
			mSelectIndex = NewIndex;
		}
	}
	else if (CInput::PushKey(VK_RETURN)) {
		Decide(mSelectIndex);
	}
	// �A�C�e���������Ă��Ȃ��ꍇ�ł��G���^�[�L�[�ŕ��鏈��
	else if (CurrentItemCount == 0 && CInput::PushKey(VK_RETURN)) {
		Close();
	}

	mpBackground->Update();
	for (const auto& itemPair : mNoItems) {
		CImage* item = itemPair.second;
		item->Update();
	}
	mpSelectFrame->Update();
}

// �A�C�e�����I���\���ǂ���
bool CInventoryMenu::IsValidSelection(int index) {
	// �C���x���g���̃A�C�e���ƁA�v���C���[�̃A�C�e�����m�F
	if (mPlayerItems[index].first == PlayerItem::INVINCIBLE_ITEM &&
		CPlayer::Instance()->HasItem(CPlayer::ItemType::INVINCIBLE)) {
		return true;
	}
	else if (mPlayerItems[index].first == PlayerItem::HEALING_ITEM &&
		CPlayer::Instance()->HasItem(CPlayer::ItemType::HEALING)) {
		return true;
	}
	else if (mPlayerItems[index].first == PlayerItem::ATTACK_UP_ITEM &&
		CPlayer::Instance()->HasItem(CPlayer::ItemType::ATTACK_UP)) {
		return true;
	}
	return false;

	// ����Ȃ�����
	//// index �� mPlayerItems ���X�g�͈͓̔��ɂ��邱�Ƃ��m�F
	//if (index < 0 || index >= mPlayerItems.size()) {
	//	return false;
	//}
}

void CInventoryMenu::Render()
{
	CPlayer* player = CPlayer::Instance();
	mpBackground->Render();

	// �I������Ă���A�C�e���݂̂�`�悷��
	for (int i = 0; i < mPlayerItems.size(); ++i) {
		// �A�C�e�����v���C���[�������Ă��邩�ǂ������m�F
		bool playerHasItem = false;
		switch (mPlayerItems[i].first) {
		case PlayerItem::INVINCIBLE_ITEM:
			playerHasItem = player->HasItem(CPlayer::ItemType::INVINCIBLE);
			break;
		case PlayerItem::HEALING_ITEM:
			playerHasItem = player->HasItem(CPlayer::ItemType::HEALING);
			break;
		case PlayerItem::ATTACK_UP_ITEM:
			playerHasItem = player->HasItem(CPlayer::ItemType::ATTACK_UP);
			break;
		default:
			break;
		}

		// �A�C�e�����v���C���[�������Ă���ꍇ�ɂ̂ݕ`�悷��
		if (playerHasItem) {
			if (i == mSelectIndex) {
				// �I�����ꂽ�A�C�e���̏ꍇ�A�I���t���[����`�悷��
				CImage* selectedItem = mPlayerItems[i].second;
				mpSelectFrame->SetPos(selectedItem->GetPos());
				mpSelectFrame->Render();
			}
			mPlayerItems[i].second->Render();
		}
	}

	// �A�C�e���������Ă��Ȃ��ꍇ�́AmNoItems�̉摜��`�悷��
	if (!player->HasItem(CPlayer::ItemType::INVINCIBLE) &&
		!player->HasItem(CPlayer::ItemType::HEALING) &&
		!player->HasItem(CPlayer::ItemType::ATTACK_UP)) {
		for (const auto& itemPair : mNoItems) {
			itemPair.second->Render();
		}
	}
}

void CInventoryMenu::SetPlayer(CPlayer* player)
{
	mPlayer = player;
}