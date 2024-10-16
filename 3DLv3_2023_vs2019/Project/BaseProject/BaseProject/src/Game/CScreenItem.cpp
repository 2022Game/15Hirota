#include "CScreenItem.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CImage.h"
#include "CPlayer.h"
#include "CStageManager.h"

#define MENU_ALPHA 0.75f

// �R���X�g���N�^
CScreenItem::CScreenItem()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eGame)
	, mIsOpened(false)
{
	// �i���o�[�摜
	const char* numberItems[] = { "UI/Item/ScreenItems(Number3).png","UI/Item/ScreenItems(Number2).png", "UI/Item/ScreenItems(Number1).png" };
	float itemWidth = -20.0f;
	int numberCount = 3;
	float spaceX = (float)WINDOW_WIDTH * 0.4f / (numberCount + 1);
	for (int i = 0; i < numberCount; i++)
	{
		CImage* item = new CImage
		(
			numberItems[i],
			ETaskPriority::eUI, 0, ETaskPauseType::eGame,
			false, false
		);
		item->SetSize(100.0f, 150.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = (float)WINDOW_WIDTH - spaceX * (i + 1) - itemWidth;
		float posY = (float)WINDOW_HEIGHT * 0.74f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mNumberItems.push_back(item);
	}

	// �o�b�N�摜
	int stageMenuCount = 3;
	for (int i = 0; i < stageMenuCount; i++)
	{
		CImage* item = new CImage
		(
			"UI/Item/ScreenItem.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eGame,
			false, false
		);
		item->SetSize(200.0f, 250.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = (float)WINDOW_WIDTH - spaceX * (i + 1) - itemWidth;
		float posY = (float)WINDOW_HEIGHT * 0.9f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mNoItems.push_back(std::make_pair(PlayerItem::NONE, item));
	}

	// �A�C�e���摜
	for (int i = 0; i < stageMenuCount; i++)
	{
		PlayerItem playerItemType;
		const char* imagePath;

		// mPlayerItems�ɍ��킹�ĉ摜�ƃA�C�e���̎�ނ�ݒ�
		switch (i)
		{
		case 0:
			playerItemType = PlayerItem::ATTACK_UP_ITEM;
			imagePath = "UI/Item/ScreenItems(Attack).png";
			break;
		case 1:
			playerItemType = PlayerItem::HEALING_ITEM;
			imagePath = "UI/Item/ScreenItems(Healing).png";
			break;
		case 2:
			playerItemType = PlayerItem::INVINCIBLE_ITEM;
			imagePath = "UI/Item/ScreenItem(Star).png";
			break;
		default:
			playerItemType = PlayerItem::NONE;
			imagePath = "UI/Item/ScreenItem.png";
			break;
		}

		// mPlayerItems�ɃA�C�e���Ɖ摜��ǉ�
		CImage* playerItem = new CImage
		(
			imagePath,
			ETaskPriority::eUI, 0, ETaskPauseType::eGame,
			false, false
		);
		playerItem->SetSize(200.0f, 250.0f);
		playerItem->SetCenter(playerItem->GetSize() * 0.5f);
		float posX = (float)WINDOW_WIDTH - spaceX * (i + 1) - itemWidth;
		float posY = (float)WINDOW_HEIGHT * 0.9f;
		playerItem->SetPos(posX, posY);
		playerItem->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mPlayerItems.push_back(std::make_pair(playerItemType, playerItem));
	}

	// �ԍ��̉摜
	//std::vector<CImage*> mNumberItems;

	SetEnable(false);
	SetShow(false);
}

// �f�X�g���N�^
CScreenItem::~CScreenItem()
{
	CStageManager::RemoveTask(this);
	// �폜�����Ƃ��Ƀ��j���[���J�����}���ł���΁A
	// ���j���[�����
	if (mIsOpened)
	{
		Close();
	}
}

// �J��
void CScreenItem::Open()
{
	// ���ɊJ���Ă�����A�������Ȃ�
	if (mIsOpened) return;

	mIsOpened = true;
	SetEnable(true);
	SetShow(true);

	//CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	//CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
}

// ����
void CScreenItem::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	//CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O������
	mIsOpened = false;
}

// �J���Ă��邩�ǂ���
bool CScreenItem::IsOpened() const
{
	return mIsOpened;
}

// �ǂ̃��j���[�ɂ��邩
void CScreenItem::Decide(int select)
{
	CPlayer* player = CPlayer::Instance();
	PlayerItem selectedItem = mPlayerItems[select].first;
	switch (selectedItem)
	{
	case PlayerItem::NONE:
		break;
		// ���G�A�C�e�����擾�����Ƃ��̏���
	case PlayerItem::INVINCIBLE_ITEM:
		player->UseInvincibleItem();
		break;
		// �񕜃A�C�e�����擾�����Ƃ��̏���
	case PlayerItem::HEALING_ITEM:
		player->UseHealingItem();
		break;
		// �U���̓A�b�v�A�C�e�����擾�����Ƃ��̏���
	case PlayerItem::ATTACK_UP_ITEM:
		player->UseAttackPotion();
		/*break;
	case PlayerItem::DEFENSE_ITEM:
		break;*/
	}
}

void CScreenItem::Update()
{
	// 1�ԃL�[���������ꍇ�͖��G�A�C�e���A
	// 2�ԃL�[���������ꍇ�͉񕜃A�C�e���A
	// 3�ԃL�[���������ꍇ�͍U���̓A�b�v�A�C�e����I������

	CPlayer* player = CPlayer::Instance();
	bool jump = player->IsJumping();
	if (!jump)
	{
		if (CInput::PushKey('3'))
		{
			Decide(0); // ���G�A�C�e����I��
		}
		else if (CInput::PushKey('2'))
		{
			Decide(1); // �񕜃A�C�e����I��

		}
		else if (CInput::PushKey('1'))
		{
			Decide(2); // �U���̓A�b�v�A�C�e����I��
		}
	}
}

void CScreenItem::Render()
{
	CPlayer* player = CPlayer::Instance();
	bool hasItem = false;

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

		if (playerHasItem)
		{
			mPlayerItems[i].second->Render();
		}
	}

	// mNoItems�̉摜��`�悷��
	for (const auto& itemPair : mNoItems) {
		itemPair.second->Render();
	}

	// mNumber�̉摜��`�悷��
	for (int i = 0; i < mNumberItems.size(); i++)
	{
		CImage* item = mNumberItems[i];
		item->Render();
	}
}

void CScreenItem::SetPlayer(CPlayer* player)
{
	mPlayer = player;
}