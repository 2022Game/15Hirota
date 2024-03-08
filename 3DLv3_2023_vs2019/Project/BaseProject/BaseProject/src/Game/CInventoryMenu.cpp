#include "CInventoryMenu.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"


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

	// アイテムを持っていないときの画像
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
	float invinciblePosY = spaceY * 1; // 上から1番目の位置
	float healingPosY = spaceY * 2; // 上から2番目の位置
	float attackPotionPosY = spaceY * 3;
	for (int i = 0; i < ItemCount; i++)
	{
		// 無敵アイテム
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

		// 回復アイテム
		CImage* healing = new CImage
		(
			"UI\\Item\\Health Recovery Items.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		healing->SetCenter(healing->GetSize() * 0.5f);
		float healingPosX = (1280.0f - 1024.0f + healing->GetSize().X()) * 0.5f + 100.0f;
		healing->SetPos(healingPosX, healingPosY);
		healing->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(PlayerItem::HEALING_ITEM, healing));

		// 攻撃力アップアイテム
		CImage* attackPotion = new CImage
		(
			"UI\\Item\\AttackPotion.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		attackPotion->SetCenter(attackPotion->GetSize() * 0.5f);
		float attackPotionPosX = (1280.0f - 1034.0f + attackPotion->GetSize().X()) * 0.5f + 100.0f;
		attackPotion->SetPos(attackPotionPosX, attackPotionPosY);
		attackPotion->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(PlayerItem::ATTACK_UP_ITEM, attackPotion));
	}

	// アイテムの枠画像
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
	SetEnable(true);
	SetShow(true);

	mSelectIndex = 0;
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

void CInventoryMenu::Close()
{
	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
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
		break;
		// 無敵アイテムを取得したときの処理
	case PlayerItem::INVINCIBLE_ITEM:
		player->UseInvincibleItem();
		break;
		// 回復アイテムを取得したときの処理
	case PlayerItem::HEALING_ITEM:
		player->UseHealingItem();
		break;
	case PlayerItem::ATTACK_UP_ITEM:
		break;
	case PlayerItem::DEFENSE_ITEM:
		break;
	}

	Close();
}

void CInventoryMenu::Update()
{
	bool playerHasItem = !mPlayerItems.empty();
	bool noItemExists = !mNoItems.empty();
	CPlayer* player = CPlayer::Instance();

	if (playerHasItem) {

		int itemCount = mPlayerItems.size();
		if (CInput::PushKey(VK_UP))
		{
			mSelectIndex = (mSelectIndex + itemCount - 1) % itemCount;
		}
		else if (CInput::PushKey(VK_DOWN))
		{
			mSelectIndex = (mSelectIndex + 1) % itemCount;
		}
		else if (CInput::PushKey(VK_RETURN))
		{
			Decide(mSelectIndex);
		}

		mpBackground->Update();
		// アイテムの更新と選択フレームの設定
		for (int i = 0; i < mPlayerItems.size(); ++i) {
			if (i == mSelectIndex) {
				mpSelectFrame->SetPos(mPlayerItems[i].second->GetPos());
			}
			mPlayerItems[i].second->Update();
		}
	}
	else if (noItemExists) {
		// アイテムが存在しない場合は、通常のアップデート
		for (const auto& itemPair : mNoItems) {
			itemPair.second->Update();
		}
	}
	mpSelectFrame->Update();
}

void CInventoryMenu::Render()
{
	CPlayer* player = CPlayer::Instance();
	mpBackground->Render();

	// 選択されているアイテムのみを描画する
	for (int i = 0; i < mPlayerItems.size(); ++i) {
		// アイテムがプレイヤーが持っているかどうかを確認
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

		// アイテムがプレイヤーが持っている場合にのみ描画する
		if (playerHasItem) {
			if (i == mSelectIndex) {
				// 選択されたアイテムの場合、選択フレームを描画する
				CImage* selectedItem = mPlayerItems[i].second;
				mpSelectFrame->SetPos(selectedItem->GetPos());
				mpSelectFrame->Render();
			}
			mPlayerItems[i].second->Render();
		}
	}

	// アイテムを持っていない場合は、mNoItemsの画像を描画する
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